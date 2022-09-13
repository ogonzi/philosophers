/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:14:04 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/13 10:17:18 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

int	ft_usleep_ms(int sleep_ms)
{
	if (usleep(sleep_ms) == -1)
	{
		ft_print_error(ERR_USLEEP);
		return (1);
	}
	return (0);
}

int	ft_any_philo_dead(t_pthread *pthread)
{
	int	i;

	i = -1;
	while (++i < pthread->args.num_philo)
	{
		if (pthread[i - pthread->philo.philo_num].philo.died == 1)
			return (1);
	}
	return (0);
}

void	ft_die_sequence(t_pthread *pthread, long int *timestamp)
{
	if (ft_usleep_ms((pthread->args.time_to_die + 5) * 1000) == 1)
		return ;
	if (ft_get_time(timestamp) == 1)
		return ;
	*timestamp = *timestamp - pthread->args.start_tv_msec;
	if (ft_any_philo_dead(pthread) == 0)
		ft_print_state_change(*timestamp, pthread->philo.philo_num + 1, DIE_CODE);
	pthread->philo.died = 1;
}

void	ft_join_pthread(t_pthread *pthread)
{
	int	i;

	i = -1;
	while (++i < pthread[0].args.num_philo)
	{
		pthread_join(pthread[i].tid, NULL);
	}
}

void	ft_destroy_mutex(t_pthread *pthread)
{
	int	i;
	int	errnum;

	i = -1;
	while (++i < pthread[0].args.num_philo)
	{
		if (pthread[i].philo.forks_used != 0)
			pthread_mutex_unlock(&pthread[i].lock);
		errnum = pthread_mutex_destroy(&pthread[i].lock);
		if (errnum != 0)
		{
			ft_print_error(ERR_MUTEX_DESTROY);
			printf("%s\n", strerror(errnum));
		}
	}
}

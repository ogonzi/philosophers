/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:14:04 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/16 16:16:44 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

int	ft_usleep_usec(int sleep_usec)
{
	if (usleep(sleep_usec) == -1)
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
	if (ft_usleep_usec((pthread->args.time_to_die) * 1000) == 1)
		return ;
	if (ft_any_philo_dead(pthread) == 0)
	{
		pthread->philo.died = 1;
		ft_usleep_usec(1000);
		if (ft_get_time(timestamp) == 1)
			return ;
		*timestamp = *timestamp - pthread->args.start_tv_usec;
		ft_print_state_change(*timestamp / 1000,
								pthread->philo.philo_num + 1, DIE_CODE);
	}
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
			pthread_mutex_unlock(&pthread[i].fork_lock);
		errnum = pthread_mutex_destroy(&pthread[i].fork_lock);
		if (errnum != 0)
		{
			ft_print_error(ERR_MUTEX_DESTROY);
			printf("%s\n", strerror(errnum));
		}
		pthread_mutex_destroy(&pthread[0].die_lock);
	}
}

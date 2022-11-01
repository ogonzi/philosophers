/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:14:04 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/01 13:40:07 by ogonzale         ###   ########.fr       */
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
		return (ft_print_error(ERR_USLEEP));
	return (0);
}
/*
int	ft_any_philo_dead(t_pthread *pthread)
{
	int	i;

	i = -1;
	if (pthread_mutex_lock(pthread->all_lock) != 0)
		return (ft_print_error(ERR_MUTEX_LOCK));
	while (++i < pthread->args.num_philo)
		if (pthread[i - pthread->philo.philo_num].philo.died == 1)
		{
			pthread_mutex_unlock(pthread->all_lock);
			return (1);
		}
	if (pthread_mutex_unlock(pthread->all_lock))
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	return (0);
}
*/
int	ft_any_philo_dead(t_pthread *pthread)
{
	if (*pthread->end == 1)
		return (1);
	return (0);
}

int	ft_die_sequence(t_pthread *pthread, long int *timestamp)
{
	if (*pthread->end != 1)
	{
		if (pthread_mutex_lock(pthread->all_lock) != 0)
			return (ft_print_error(ERR_MUTEX_LOCK));
		pthread->philo.died = 1;
		*pthread->end = 1;
		if (ft_get_time(timestamp) == 1)
			return (1);
		*timestamp = *timestamp - pthread->args.start_tv_usec;
		ft_print_state_change(*timestamp / 1000,
				pthread->philo.philo_num + 1, DIE_CODE);
		if (pthread_mutex_unlock(pthread->all_lock) != 0)
			return (ft_print_error(ERR_MUTEX_UNLOCK));
	}
	return (0);
}

int	ft_join_pthread(t_pthread *pthread)
{
	int	i;

	i = -1;
	while (++i < pthread[0].args.num_philo)
		if (pthread_join(pthread[i].tid, NULL) != 0)
			return (ft_print_error(ERR_JOIN));
	return (0);
}

int	ft_destroy_mutex(t_pthread *pthread)
{
	int	i;

	//if (pthread_mutex_unlock(pthread->all_lock) != 0)
	//	return (ft_print_error(ERR_MUTEX_UNLOCK));
	i = -1;
	while (++i < pthread[0].args.num_philo)
	{
		if (pthread[i].philo.forks_used != 0)
			pthread_mutex_unlock(&pthread[i].fork_lock);
		if (pthread_mutex_destroy(&pthread[i].fork_lock) != 0)
			return (ft_print_error(ERR_MUTEX_DESTROY));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:14:04 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/01 18:36:37 by ogonzale         ###   ########.fr       */
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

int	ft_die_sequence(t_pthread *pthread, long int *timestamp)
{
	if (*pthread->end != 1)
	{
		if (pthread_mutex_lock(pthread->all_lock) != 0)
			return (ft_print_error(ERR_MUTEX_LOCK));
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

int	ft_unlock_fork_lock(t_pthread *this_pthread, t_pthread *left_pthread,
						int fork_flag)
{
	if (pthread_mutex_lock(this_pthread->all_lock) != 0)
		return (ft_print_error(ERR_MUTEX_LOCK));
	if (pthread_mutex_unlock(&this_pthread->fork_lock) != 0)
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	if (fork_flag == 1)
	{
		if (pthread_mutex_unlock(&left_pthread->fork_lock) != 0)
			return (ft_print_error(ERR_MUTEX_UNLOCK));
		this_pthread->philo.forks_used = 0;
	}
	if (pthread_mutex_unlock(this_pthread->all_lock) != 0)
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	return (1);
}

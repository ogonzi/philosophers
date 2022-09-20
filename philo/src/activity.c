/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:45:58 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/20 10:12:09 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	ft_grab_forks(t_pthread *this_pthread, t_pthread *left_pthread,
					long int *timestamp)
{
	if (pthread_mutex_lock(&this_pthread->fork_lock) != 0)
	{
		ft_print_error(ERR_MUTEX_LOCK);
		return (1);
	}
	if (ft_any_philo_dead(this_pthread) == 1)
	{
		pthread_mutex_unlock(&this_pthread->fork_lock);
		return (0);
	}
	if (ft_print_sequence(this_pthread, FORK_CODE, timestamp) != 0)
		return (1);
	this_pthread->philo.forks_used++;
	if (left_pthread != NULL)
	{
		if (pthread_mutex_lock(&left_pthread->fork_lock) != 0)
		{
			ft_print_error(ERR_MUTEX_LOCK);
			return (1);
		}
		if (ft_print_sequence(this_pthread, FORK_CODE, timestamp) != 0)
			return (1);
		this_pthread->philo.forks_used++;
	}
	return (0);
}

int	ft_leave_forks(t_pthread *this_pthread, t_pthread *left_pthread)
{
	this_pthread->philo.forks_used--;
	if (pthread_mutex_unlock(&this_pthread->fork_lock) != 0)
	{
		ft_print_error(ERR_MUTEX_UNLOCK);
		return (1);
	}
	if (left_pthread != NULL)
	{
		this_pthread->philo.forks_used--;
		if (pthread_mutex_unlock(&left_pthread->fork_lock) != 0)
		{
			ft_print_error(ERR_MUTEX_UNLOCK);
			return (1);
		}
	}
	return (0);
}

int	ft_eat(t_pthread *this_pthread, t_pthread *left_pthread,
		long int *timestamp)
{
	if (ft_grab_forks(this_pthread, left_pthread, timestamp) == 1)
		return (1);
	if (this_pthread->philo.forks_used != 2)
	{
		if (ft_usleep_usec(this_pthread->args.time_to_die * 1000) != 0)
			return (1);
		ft_die_sequence(this_pthread, timestamp);
		return (0);
	}
	ft_print_state_change(*timestamp / 1000, this_pthread->philo.philo_num + 1,
		EAT_CODE);
	if (pthread_mutex_unlock(this_pthread->all_lock) != 0)
	{
		ft_print_error(ERR_MUTEX_UNLOCK);
		return (1);
	}
	this_pthread->philo.start_time = *timestamp / 1000;
	this_pthread->philo.thinking = 0;
	this_pthread->philo.eating = 1;
	if (ft_usleep_usec(this_pthread->args.time_to_eat * 1000) == 1)
		return (1);
	this_pthread->philo.eat_counter++;
	if (ft_leave_forks(this_pthread, left_pthread) == 1)
		return (1);
	return (0);
}

int	ft_sleep(t_pthread *this_pthread, long int *timestamp)
{
	if (ft_print_sequence(this_pthread, SLEEP_CODE, timestamp) != 0)
		return (1);
	this_pthread->philo.eating = 0;
	this_pthread->philo.sleeping = 1;
	if (ft_usleep_usec(this_pthread->args.time_to_sleep * 1000) == 1)
		return (1);
	return (0);
}

int	ft_think(t_pthread *this_pthread, long int *timestamp)
{
	if (ft_print_sequence(this_pthread, THINK_CODE, timestamp) != 0)
		return (1);
	this_pthread->philo.sleeping = 0;
	this_pthread->philo.thinking = 1;
	return (0);
}

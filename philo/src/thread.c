/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:02:53 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/11 10:56:27 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	ft_philo_will_die(t_pthread *pthread)
{
	long int		timestamp;

	if (pthread->philo.eating == 1
		&& pthread->args.time_to_eat > pthread->args.time_to_die)
	{
		ft_die_sequence(pthread, &timestamp);
		return (1);
	}
	else if (pthread->philo.sleeping == 1)
	{
		if (ft_get_time(&timestamp) == 1)
			return (1);
		timestamp = timestamp - pthread->args.start_tv_msec;
		if (timestamp - pthread->philo.start_time + pthread->args.time_to_sleep
			> pthread->args.time_to_die)
		{
			ft_die_sequence(pthread, &timestamp);
			return (1);
		}
	}
	return (0);
}

int	ft_grab_forks(t_pthread *this_pthread, t_pthread *left_pthread)
{
	long int	timestamp;

	if (pthread_mutex_lock(&this_pthread->lock) != 0)
	{
		ft_print_error(ERR_MUTEX_LOCK);
		return (1);
	}
	if (ft_get_time(&timestamp) == 1)
		return (0);
	timestamp = timestamp - this_pthread->args.start_tv_msec;
	ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, FORK_CODE);
	if (left_pthread != NULL)
	{
		if (pthread_mutex_lock(&left_pthread->lock) != 0)
		{
			ft_print_error(ERR_MUTEX_LOCK);
			return (1);
		}
		if (ft_get_time(&timestamp) == 1)
			return (0);
		timestamp = timestamp - this_pthread->args.start_tv_msec;
		ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, FORK_CODE);
	}
	return (0);
}

int	ft_leave_forks(t_pthread *this_pthread, t_pthread *left_pthread)
{
	if (pthread_mutex_unlock(&this_pthread->lock) != 0)
	{
		ft_print_error(ERR_MUTEX_UNLOCK);
		return (1);
	}
	if (left_pthread != NULL)
	{
		if (pthread_mutex_unlock(&left_pthread->lock) != 0)
		{
			ft_print_error(ERR_MUTEX_UNLOCK);
			return (1);
		}
	}
	return (0);
}

void	*ft_thread_routine(void *pthread)
{
	t_pthread		*this_pthread;
	t_pthread		*left_pthread;
	long int		timestamp;

	this_pthread = (t_pthread *)pthread;
	if (this_pthread->args.num_philo == 1)
		left_pthread = NULL;
	else if (this_pthread->philo.philo_num > 0)
		left_pthread = &this_pthread[this_pthread->philo.philo_num - 1];
	else
		left_pthread = &this_pthread[this_pthread->args.num_philo - 1];
	if (this_pthread->philo.philo_num % 2 == 1)
		usleep(this_pthread->args.time_to_eat * 1000);
	while (this_pthread->philo.eat_counter < this_pthread->args.max_meals
			|| this_pthread->args.max_meals == -1)
	{
		if (this_pthread->philo.eating == 0
			&& this_pthread->philo.sleeping == 0
			&& this_pthread->philo.thinking == 0)
		{
			if (ft_grab_forks(this_pthread, left_pthread) == 1)
				return (0);
			if (ft_get_time(&timestamp) == 1)
				return (0);
			timestamp = timestamp - this_pthread->args.start_tv_msec;
			ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, EAT_CODE);
			this_pthread->philo.start_time = timestamp;
			this_pthread->philo.eating = 1;
			this_pthread->philo.eat_counter = 1;
			if (ft_philo_will_die(this_pthread) == 1)
				return (0);
			if (ft_usleep_ms(this_pthread->args.time_to_eat * 1000) == 1)
				return (0);
		}
		else if (this_pthread->philo.eating == 1)
		{
			ft_leave_forks(this_pthread, left_pthread);
			this_pthread->philo.eating = 0;
			if (ft_get_time(&timestamp) == 1)
				return (0);
			timestamp = timestamp - this_pthread->args.start_tv_msec;
			ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, SLEEP_CODE);
			this_pthread->philo.sleeping = 1;
			if (ft_philo_will_die(this_pthread) == 1)
				return (0);
			if (ft_usleep_ms(this_pthread->args.time_to_sleep * 1000) == 1)
				return (0);
		}
		else if (this_pthread->philo.sleeping == 1)
		{
			this_pthread->philo.sleeping = 0;
			if (ft_get_time(&timestamp) == 1)
				return (0);
			timestamp = timestamp - this_pthread->args.start_tv_msec;
			ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, THINK_CODE);
			this_pthread->philo.thinking = 1;
		}
		else if (this_pthread->philo.thinking == 1)
		{
			this_pthread->philo.thinking = 0;
			if (ft_grab_forks(this_pthread, left_pthread) == 1)
				return (0);
			if (ft_get_time(&timestamp) == 1)
				return (0);
			timestamp = timestamp - this_pthread->args.start_tv_msec;
			ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, EAT_CODE);
			this_pthread->philo.eating = 1;
			this_pthread->philo.start_time = timestamp;
			this_pthread->philo.eat_counter += 1;
			if (ft_philo_will_die(this_pthread) == 1)
				return (0);
			if (ft_usleep_ms(this_pthread->args.time_to_eat * 1000) == 1)
				return (0);
		}
	}
	return (0);
}

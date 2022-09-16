/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:45:58 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/16 16:38:48 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

void	ft_get_pthreads(void *pthread, t_pthread **this_pthread,
						t_pthread **left_pthread)
{
	int	num_philo;

	*this_pthread = (t_pthread *)pthread;
	num_philo = (*this_pthread)->args.num_philo;
	if (num_philo == 1)
		*left_pthread = NULL;
	else if ((*this_pthread)->philo.philo_num > 0)
		*left_pthread = &(*this_pthread)[-1];
	else
		*left_pthread = &(*this_pthread)[num_philo - 1];
}

int	ft_grab_forks(t_pthread *this_pthread, t_pthread *left_pthread,
					long int *timestamp)
{
	if (pthread_mutex_lock(&this_pthread->fork_lock) != 0)
	{
		ft_print_error(ERR_MUTEX_LOCK);
		return (1);
	}
	if (ft_get_time(timestamp) == 1)
		return (1);
	*timestamp = *timestamp - this_pthread->args.start_tv_usec;
	ft_print_state_change(*timestamp / 1000,
							this_pthread->philo.philo_num + 1, FORK_CODE);
	this_pthread->philo.forks_used++;
	if (left_pthread != NULL)
	{
		if (pthread_mutex_lock(&left_pthread->fork_lock) != 0)
		{
			ft_print_error(ERR_MUTEX_LOCK);
			return (1);
		}
		if (ft_get_time(timestamp) == 1)
			return (1);
		*timestamp = *timestamp - this_pthread->args.start_tv_usec;
		ft_print_state_change(*timestamp / 1000,
								this_pthread->philo.philo_num + 1, FORK_CODE);
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
		ft_die_sequence(this_pthread, timestamp);
		return (0);
	}
	ft_print_state_change(*timestamp / 1000, this_pthread->philo.philo_num + 1,
			EAT_CODE);
	this_pthread->philo.start_time = *timestamp;
	if (this_pthread->philo.thinking == 1)
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
	if (ft_get_time(timestamp) == 1)
		return (1);
	*timestamp = *timestamp - this_pthread->args.start_tv_usec;
	ft_print_state_change(*timestamp / 1000,
							this_pthread->philo.philo_num + 1, SLEEP_CODE);
	this_pthread->philo.eating = 0;
	this_pthread->philo.sleeping = 1;
	if (ft_usleep_usec(this_pthread->args.time_to_sleep * 1000) == 1)
		return (1);
	return (0);
}

int	ft_think(t_pthread *this_pthread, long int *timestamp)
{
	if (ft_get_time(timestamp) == 1)
		return (1);
	*timestamp = *timestamp - this_pthread->args.start_tv_usec;
	ft_print_state_change(*timestamp / 1000,
							this_pthread->philo.philo_num + 1, THINK_CODE);
	this_pthread->philo.sleeping = 0;
	this_pthread->philo.thinking = 1;
	if (ft_usleep_usec(500) == 1)
		return (1);
	return (0);
}

void	*ft_thread_routine(void *pthread)
{
	t_pthread	*this_pthread;
	t_pthread	*left_pthread;
	long int	timestamp;

	ft_get_pthreads(pthread, &this_pthread, &left_pthread);
	if (this_pthread->philo.philo_num % 2 == 1)
		if (ft_usleep_usec(this_pthread->args.time_to_eat * 1000) == 1)
			return (0);
	while (this_pthread->philo.eat_counter < this_pthread->args.max_meals
			|| this_pthread->args.max_meals == -1)
	{
		if (ft_eat(this_pthread, left_pthread, &timestamp) == 1)
			return (0);
		if (this_pthread->philo.died == 1)
			return (pthread);
		if (this_pthread->philo.eat_counter == this_pthread->args.max_meals)
			break ;
		if (ft_sleep(this_pthread, &timestamp) == 1)
			return (0);
		if (ft_think(this_pthread, &timestamp) == 1)
			return (0);
	}
	return (pthread);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:02:53 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/10 10:33:08 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	ft_philo_will_die(t_pthread *pthread)
{
	struct timeval	time;
	int				timestamp;

	if (pthread->philo.eating == 1
		&& pthread->args.time_to_eat > pthread->args.time_to_die)
	{
		usleep(pthread->args.time_to_die * 1000);
		gettimeofday(&time, NULL);
		timestamp = time.tv_usec / 1000;
		ft_print_state_change(timestamp, pthread->philo.philo_num + 1, DIE_CODE);
		return (1);
	}
	else if (pthread->philo.sleeping == 1)
	{
		gettimeofday(&time, NULL);
		timestamp = time.tv_usec / 1000;
		if (timestamp - pthread->philo.start_time + pthread->args.time_to_sleep
			> pthread->args.time_to_die)
		{
			usleep(pthread->args.time_to_die * 1000);
			gettimeofday(&time, NULL);
			timestamp = time.tv_usec / 1000;
			ft_print_state_change(timestamp, pthread->philo.philo_num + 1, DIE_CODE);
			return (1);
		}
	}
	return (0);
}

void	*ft_thread_routine(void *pthread)
{
	struct timeval	time;
	t_pthread		*this_pthread;
	int				timestamp;

	this_pthread = (t_pthread *)pthread;
	//if (this_pthread->philo.philo_num % 2 == 1)
	//	usleep(this_pthread->args.time_to_eat * 1000);
	while (this_pthread->philo.eat_counter < this_pthread->args.max_meals
			|| this_pthread->args.max_meals == -1)
	{
		if (this_pthread->philo.eating == 0
			&& this_pthread->philo.sleeping == 0
			&& this_pthread->philo.thinking == 0)
		{
			gettimeofday(&time, NULL);
			timestamp = time.tv_usec / 1000;
			ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, EAT_CODE);
			this_pthread->philo.start_time = timestamp;
			this_pthread->philo.eating = 1;
			this_pthread->philo.eat_counter = 1;
			if (ft_philo_will_die(this_pthread) == 1)
				return (0);
			usleep(this_pthread->args.time_to_eat * 1000);
		}
		else if (this_pthread->philo.eating == 1)
		{
			this_pthread->philo.eating = 0;
			gettimeofday(&time, NULL);
			timestamp = time.tv_usec / 1000;
			ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, SLEEP_CODE);
			this_pthread->philo.sleeping = 1;
			if (ft_philo_will_die(this_pthread) == 1)
				return (0);
			usleep(this_pthread->args.time_to_sleep * 1000);
		}
		else if (this_pthread->philo.sleeping == 1)
		{
			this_pthread->philo.sleeping = 0;
			gettimeofday(&time, NULL);
			timestamp = time.tv_usec / 1000;
			ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, THINK_CODE);
			this_pthread->philo.thinking = 1;
		}
		else if (this_pthread->philo.thinking == 1)
		{
			this_pthread->philo.thinking = 0;
			gettimeofday(&time, NULL);
			timestamp = time.tv_usec / 1000;
			ft_print_state_change(timestamp, this_pthread->philo.philo_num + 1, EAT_CODE);
			this_pthread->philo.eating = 1;
			this_pthread->philo.start_time = timestamp;
			this_pthread->philo.eat_counter += 1;
			if (ft_philo_will_die(this_pthread) == 1)
				return (0);
			usleep(this_pthread->args.time_to_eat * 1000);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:26:38 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/20 10:10:10 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	ft_print_sequence(t_pthread *pthread, int status_code, long int *timestamp)
{
	if (pthread_mutex_lock(pthread->all_lock) != 0)
	{
		ft_print_error(ERR_MUTEX_LOCK);
		return (1);
	}
	if (ft_get_time(timestamp) == 1)
		return (1);
	*timestamp = *timestamp - pthread->args.start_tv_usec;
	ft_print_state_change(*timestamp / 1000,
		pthread->philo.philo_num + 1, status_code);
	if (pthread->philo.forks_used != 1)
	{
		if (pthread_mutex_unlock(pthread->all_lock) != 0)
		{
			ft_print_error(ERR_MUTEX_UNLOCK);
			return (1);
		}
	}
	return (0);
}

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

void	*ft_thread_routine(void *pthread)
{
	t_pthread	*this_pthread;
	t_pthread	*left_pthread;
	long int	t;

	ft_get_pthreads(pthread, &this_pthread, &left_pthread);
	if (this_pthread->philo.philo_num % 2 == 1)
		if (ft_usleep_usec(this_pthread->args.time_to_eat * 1000) == 1)
			return (0);
	while (this_pthread->philo.eat_counter < this_pthread->args.max_meals
		|| this_pthread->args.max_meals == -1)
	{
		if (ft_any_philo_dead(this_pthread) == 1)
			return (0);
		if (ft_eat(this_pthread, left_pthread, &t) == 1)
			return (0);
		if (this_pthread->philo.eat_counter == this_pthread->args.max_meals)
			break ;
		if (ft_any_philo_dead(this_pthread) == 1)
			return (0);
		if (ft_sleep(this_pthread, &t) == 1)
			return (0);
		if (ft_any_philo_dead(this_pthread) == 1)
			return (0);
		if (ft_think(this_pthread, &t) == 1)
			return (0);
	}
	return (pthread);
}

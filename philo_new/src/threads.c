/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:48:29 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/04 18:41:03 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_loop_main_thread(t_data *data)
{
	while (data->death == 0)
	{
		if (ft_routine_is_finished(data) == 1)
		{
			if (pthread_mutex_unlock(&data->m_print) != 0)
				return (ft_print_error(ERR_MUTEX_UNLOCK));
			return (0);
		}
		if (ft_any_philo_died(data) == 1)
			return (0);
	}
	return (0);
}

int	ft_handle_lonely_philo(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->m_fork[philo->right_fork]) != 0)
		return (ft_print_error(ERR_MUTEX_LOCK));
	ft_print_state_change(ft_get_time() - philo->data->start_time,
		philo->philo_num, FORK_CODE); 
	if (ft_usleep(philo->data->time_to_die) != 0)
		return (1);
	return (0);
}

void	*ft_thread_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	if (philo->philo_num % 2 == 0)
		if (ft_usleep(philo->data->time_to_eat) != 0)
		{
			philo->data->err = 1;
			return (0);
		}
	philo->last_meal = ft_get_time() - philo->data->start_time;
	if (philo->data->num_philos == 1)
	{
		if (ft_handle_lonely_philo(philo) != 0)
		{
			philo->data->err = 1;
			return (0);
		}
	}
	else
	{
		while (philo->data->death == 0)
		{
			if (ft_eat(philo) != 0 || ft_sleep(philo) != 0
					|| ft_think(philo) != 0)
			{
				if (philo->data->err != 0)
					return (0);
				break ;
			}
		}
	}
	i = -1;
	while (++i < philo->data->num_philos)
		if (pthread_mutex_unlock(&philo->data->m_fork[i]) != 0)
		{
			philo->data->err = ft_print_error(ERR_MUTEX_UNLOCK);
			return (0);
		}
	return (0);
}

int	ft_create_pthreads(t_data *data)
{
	pthread_t	*pthread;
	int			i;

	i = -1;
	pthread = malloc(sizeof(pthread_t) * data->num_philos);
	if (pthread == NULL)
		return (ft_print_error(ERR_MEM));
	while (++i < data->num_philos)
		if (pthread_create(&pthread[i], NULL,
			&ft_thread_routine, &data->philo[i]) != 0)
			return (ft_print_error(ERR_THREAD));
	if (data->err != 0)
		return (1);
	if (ft_loop_main_thread(data) != 0)
		return (1);
	if (pthread_mutex_unlock(&data->m_print) != 0)
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(&data->m_death) != 0)
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	i = -1;
	while (++i < data->num_philos)
		if (pthread_join(pthread[i], NULL) != 0)
			return (ft_print_error(ERR_JOIN));
	free(pthread);
	return (0);
}

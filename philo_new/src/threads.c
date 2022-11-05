/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:48:29 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/05 13:44:40 by ogonzale         ###   ########.fr       */
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
			return (0);
		if (ft_any_philo_died(data) == 1)
			return (0);
	}
	return (0);
}

int	ft_handle_lonely_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_lock(&data->m_fork[philo->left_fork_index]) != 0)
		return (ft_print_error(ERR_MUTEX_LOCK));
	if (ft_print_state_change(philo, GRAB_FORK) != 0)
		return (1);
	if (ft_usleep(data->time_to_die) != 0)
		return (1);
	if (pthread_mutex_unlock(&data->m_fork[philo->left_fork_index]) != 0)
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	return (0);
}

void	*ft_thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number % 2 == 0)
		if (ft_usleep(philo->data->time_to_eat) != 0)
			return (0);
	philo->time_of_last_meal = ft_get_time() - philo->data->start_time;
	if (philo->data->number_of_philos == 1)
	{
		if (ft_handle_lonely_philo(philo) != 0)
			return (0);
	}
	else
	{
		while (philo->data->death == 0)
		{
			if (ft_eat(philo) != 0 || ft_sleep(philo) != 0
				|| ft_think(philo) != 0)
				break ;
		}
	}
	return (0);
}

int	ft_unlock_and_join(t_data *data, pthread_t *pthread)
{
	int	i;

	if (pthread_mutex_unlock(&data->m_print) != 0)
	{
		free(pthread);
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	}
	if (pthread_mutex_unlock(&data->m_death) != 0)
	{
		free(pthread);
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	}
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_join(pthread[i], NULL) != 0)
		{
			free(pthread);
			return (ft_print_error(ERR_JOIN));
		}
	}
	free(pthread);
	return (0);
}

int	ft_create_pthreads(t_data *data)
{
	pthread_t	*pthread;
	int			i;

	pthread = malloc(sizeof(pthread_t) * data->number_of_philos);
	if (pthread == NULL)
		return (ft_print_error(ERR_MEM));
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_create(&pthread[i], NULL,
				&ft_thread_routine, &data->philo[i]) != 0)
		{
			free(pthread);
			return (ft_print_error(ERR_THREAD));
		}
	}
	if (ft_loop_main_thread(data) != 0)
	{
		free(pthread);
		return (1);
	}
	if (ft_unlock_and_join(data, pthread) != 0)
		return (1);
	return (0);
}

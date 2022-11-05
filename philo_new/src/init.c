/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:53:01 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/05 13:40:39 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
		return (ft_print_error(ERR_MUTEX_INIT));
	if (pthread_mutex_init(&data->m_death, NULL) != 0)
		return (ft_print_error(ERR_MUTEX_INIT));
	data->m_fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (data->m_fork == NULL)
		return (ft_print_error(ERR_MEM));
	while (++i < data->number_of_philos)
		if (pthread_mutex_init(&data->m_fork[i], NULL) != 0)
			return (ft_print_error(ERR_MUTEX_INIT));
	return (0);
}

int	ft_init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->number_of_philos);
	if (data->philo == NULL)
		return (ft_print_error(ERR_MEM));
	while (++i < data->number_of_philos)
	{
		data->philo[i].number = i + 1;
		data->philo[i].left_fork_index = i;
		data->philo[i].right_fork_index = i + 1;
		data->philo[i].data = data;
		data->philo[i].meal_counter = 0;
	}
	data->philo[i - 1].right_fork_index = 0;
	return (0);
}

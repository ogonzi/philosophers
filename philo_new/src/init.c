/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:53:01 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/03 17:16:11 by ogonzale         ###   ########.fr       */
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
	data->m_fork = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (data->m_fork == NULL)
		return (ft_print_error(ERR_MEM));
	while (++i < data->num_philos)
		if (pthread_mutex_init(&data->m_fork[i], NULL) != 0)
			return (ft_print_error(ERR_MUTEX_INIT));
	return (0);
}

int	ft_init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	if (data->philo == NULL)
		return (ft_print_error(ERR_MEM));
	while (++i < data->num_philos)
	{
		data->philo[i].philo_num = i + 1;
		data->philo[i].left_fork = i - 1;
		data->philo[i].right_fork = i;
		data->philo[i].data = data;
	}
	data->philo[0].left_fork = i - 1;
	return (0);
}

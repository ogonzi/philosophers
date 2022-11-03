/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:48:29 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/03 19:40:22 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdlib.h>

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
	if (ft_loop_main_thread(data) != 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:10:10 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/03 19:40:02 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

int	ft_routine_is_finished(t_data *data)
{
	int	i;
	int	num_philos_full;

	i = -1;
	num_philos_full = 0;
	if (data->max_meals == -1)
		return (0);
	while (++i < data->num_philos)
	{
		if (data->philo[i].num_meals >= data->max_meals)
			num_philos_full++;
		else
			break ;
	}
	if (num_philos_full >= data->num_philos)
	{
		data->death = 1;
		if (pthread_mutex_lock(&data->m_print) != 0)
			return (ft_print_error(ERR_MUTEX_LOCK));
		return (1);
	}
	
	return (0);
}

int	ft_any_philo_died(t_data *data)
{
	int				i;
	long long int	elapsed_time;

	i = -1;
	while (++i < data->num_philos)
	{
		elapsed_time = ft_get_time() - data->start_time;
		if (data->time_to_die < elapsed_time)
		{
			if (pthread_mutex_lock(&data->m_death) != 0)
				return (ft_print_error(ERR_MUTEX_LOCK));
			ft_print_state_change(elapsed_time,
				((t_philo *)data->philo[i])->philo_num, int state_code)
			if (pthread_mutex_lock(&data->m_death) != 0)
				return (ft_print_error(ERR_MUTEX_LOCK));
			if (pthread_mutex_lock(&data->m_death) != 0)
				return (ft_print_error(ERR_MUTEX_LOCK));
			data->death = 1;
			return (1);
		}
	}
	return (0);
}

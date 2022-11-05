/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:03:28 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/05 18:56:29 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

int	ft_unlock_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->data->m_fork[philo->left_fork_index])
		!= 0)
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(&philo->data->m_fork[philo->right_fork_index])
		!= 0)
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	return (0);
}

int	ft_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->death != 0)
		return (-1);
	if (pthread_mutex_lock(&data->m_fork[philo->left_fork_index]) != 0)
		return (ft_print_error(ERR_MUTEX_LOCK));
	if (ft_print_state_change(philo, GRAB_FORK) != 0)
		return (1);
	if (pthread_mutex_lock(&data->m_fork[philo->right_fork_index]) != 0)
		return (ft_print_error(ERR_MUTEX_LOCK));
	if (data->death == 0)
	{
		if (ft_print_state_change(philo, GRAB_FORK) != 0)
			return (1);
		philo->time_of_last_meal = ft_get_time() - data->start_time;
		if (ft_print_state_change(philo, EAT) != 0)
			return (1);
		if (ft_usleep(philo->data->time_to_eat) != 0)
			return (1);
		philo->meal_counter++;
	}
	if (ft_unlock_forks(philo) != 0)
		return (1);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (philo->data->death != 0)
		return (-1);
	if (ft_print_state_change(philo, SLEEP) != 0)
		return (1);
	if (ft_usleep(philo->data->time_to_sleep) != 0)
		return (1);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (philo->data->death != 0)
		return (-1);
	if (ft_print_state_change(philo, THINK) != 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:03:28 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/04 18:13:34 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

int	ft_eat(t_philo *philo)
{
	if (philo->data->death != 0)
		return (-1);
	if (pthread_mutex_lock(&philo->data->m_fork[philo->left_fork]) != 0)
	{
		philo->data->err = 1;
		return (ft_print_error(ERR_MUTEX_LOCK));
	}
	ft_print_state_change(ft_get_time() - philo->data->start_time,
			philo->philo_num, FORK_CODE);
	if (pthread_mutex_lock(&philo->data->m_fork[philo->right_fork]) != 0)
	{
		philo->data->err = 1;
		return (ft_print_error(ERR_MUTEX_LOCK));
	}
	ft_print_state_change(ft_get_time() - philo->data->start_time,
			philo->philo_num, FORK_CODE);
	philo->last_meal = ft_get_time() - philo->data->start_time;
	ft_print_state_change(ft_get_time() - philo->data->start_time,
			philo->philo_num, EAT_CODE);
	if (ft_usleep(philo->data->time_to_eat) != 0)
	{
		philo->data->err = 1;
		return (ft_print_error(ERR_USLEEP));
	}
	if (pthread_mutex_unlock(&philo->data->m_fork[philo->left_fork]) != 0)
	{
		philo->data->err = 1;
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	}
	if (pthread_mutex_unlock(&philo->data->m_fork[philo->right_fork]) != 0)
	{
		philo->data->err = 1;
		return (ft_print_error(ERR_MUTEX_UNLOCK));
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (philo->data->death != 0)
		return (-1);
	ft_print_state_change(ft_get_time() - philo->data->start_time,
			philo->philo_num, SLEEP_CODE);
	if (ft_usleep(philo->data->time_to_sleep) != 0)
	{
		philo->data->err = 1;
		return (ft_print_error(ERR_USLEEP));
	}
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (philo->data->death != 0)
		return (-1);
	ft_print_state_change(ft_get_time() - philo->data->start_time,
			philo->philo_num, SLEEP_CODE);
	return (0);
}

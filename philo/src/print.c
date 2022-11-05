/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:24 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/05 13:49:57 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdio.h>

int	ft_print_state_change(t_philo *philo, int state)
{
	if (pthread_mutex_lock(&philo->data->m_print) != 0)
		return (ft_print_error(ERR_MUTEX_LOCK));
	if (philo->data->death == 0 || state == DIE)
	{
		if (state == GRAB_FORK)
			printf("%lld %d has taken a fork\n",
				ft_get_time() - philo->data->start_time, philo->number);
		else if (state == EAT)
			printf("%lld %d is eating\n",
				ft_get_time() - philo->data->start_time, philo->number);
		else if (state == SLEEP)
			printf("%lld %d is sleeping\n",
				ft_get_time() - philo->data->start_time, philo->number);
		else if (state == THINK)
			printf("%lld %d is thinking\n",
				ft_get_time() - philo->data->start_time, philo->number);
		else if (state == DIE)
			printf("%lld %d died\n",
				ft_get_time() - philo->data->start_time, philo->number);
	}
	if (state != DIE)
		if (pthread_mutex_unlock(&philo->data->m_print) != 0)
			return (ft_print_error(ERR_MUTEX_UNLOCK));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:27:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/03 19:29:52 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "utils.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	ft_print_error(char *s)
{
	if (write(STDERR_FILENO, "Error: ", 7) == -1)
		return (1);
	if (s)
	{
		if (write(STDERR_FILENO, s, ft_strlen(s)) == -1)
			return (1);
	}
	if (write(STDERR_FILENO, "\n", 1) == -1)
		return (1);
	return (1);
}

int	ft_cleanup(t_data *data, int destroy_mutex, int from_error)
{
	int	i;

	i = -1;
	if (pthread_mutex_unlock(&data->m_print) != 0)
		ft_print_error(ERR_MUTEX_UNLOCK);
	if (pthread_mutex_unlock(data->m_fork) != 0)
		ft_print_error(ERR_MUTEX_UNLOCK);
	if (pthread_mutex_unlock(&data->m_death) != 0)
		ft_print_error(ERR_MUTEX_UNLOCK);
	if (destroy_mutex == 1)
	{
		if (pthread_mutex_destroy(&data->m_death) != 0)
			ft_print_error(ERR_MUTEX_DESTROY);
		if (pthread_mutex_destroy(&data->m_print) != 0)
			ft_print_error(ERR_MUTEX_DESTROY);
		while (++i < data->num_philos)
			if (pthread_mutex_destroy(&data->m_fork[i]) != 0)
				ft_print_error(ERR_MUTEX_DESTROY);
	}
	free(data->philo);
	free(data->m_fork);
	free(data);
	return (from_error);
}

long long int	ft_get_time(void)
{
	struct timeval	current_time;
	long long int	time;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		ft_print_error(ERR_TIME);
		return (-1);
	}
	time = current_time.tv_sec * 1000000 + current_time.tv_usec;
	return (time);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:27:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/05 18:29:16 by ogonzale         ###   ########.fr       */
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
	write(STDERR_FILENO, "Error: ", 7);
	if (s)
		write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	ft_cleanup(t_data *data, int destroy_mutex, int from_error)
{
	int	i;

	i = -1;
	if (destroy_mutex == 1)
	{
		if (pthread_mutex_destroy(&data->m_death) != 0)
			ft_print_error(ERR_MUTEX_DESTROY);
		if (pthread_mutex_destroy(&data->m_print) != 0)
			ft_print_error(ERR_MUTEX_DESTROY);
		while (++i < data->number_of_philos)
			if (pthread_mutex_destroy(&data->m_fork[i]) != 0)
				ft_print_error(ERR_MUTEX_DESTROY);
	}
	free(data->philo);
	free(data->m_fork);
	free(data);
	return (from_error);
}

int	ft_usleep(int time)
{
	long long int	current_time;

	current_time = ft_get_time();
	while (time > ft_get_time() - current_time)
	{
		if (usleep(1) == -1)
			return (ft_print_error(ERR_USLEEP));
	}
	return (0);
}

long long int	ft_get_time(void)
{
	struct timeval	current_time;
	long long int	time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

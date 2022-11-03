/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:27:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/03 16:56:35 by ogonzale         ###   ########.fr       */
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
	if (write(2, "Error: ", 7) == -1)
		return (1);
	if (s)
	{
		if (write(2, s, ft_strlen(s)) == -1)
			return (1);
	}
	if (write(2, "\n", 1) == -1)
		return (1);
	return (1);
}

int	ft_clean_exit_error(t_data *data, int destroy_mutex)
{
	if (destroy_mutex == 1)
		printf("TODO: destroy mutex\n");
	free(data->philo);
	free(data);
	return (0);
}

int	ft_get_time(long int *time)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (ft_print_error(ERR_TIME));
	*time = current_time.tv_sec * 1000000 + current_time.tv_usec;
	return (0);
}

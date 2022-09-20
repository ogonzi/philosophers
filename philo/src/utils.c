/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:24:29 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/20 11:50:57 by ogonzale         ###   ########.fr       */
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

void	ft_print_state_change(int timestamp, int philo_num, int state_code)
{
	if (state_code == FORK_CODE)
		printf("%d %d has taken a fork\n", timestamp, philo_num);
	if (state_code == EAT_CODE)
		printf("%d %d is eating\n", timestamp, philo_num);
	if (state_code == SLEEP_CODE)
		printf("%d %d is sleeping\n", timestamp, philo_num);
	if (state_code == THINK_CODE)
		printf("%d %d is thinking\n", timestamp, philo_num);
	if (state_code == DIE_CODE)
		printf("%d %d died\n", timestamp, philo_num);
}

int	ft_allocate_pthread(t_pthread **pthread, int philo_num)
{
	*pthread = malloc(sizeof(t_pthread) * philo_num);
	if (*pthread == NULL)
		return (ft_print_error(ERR_MEM));
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

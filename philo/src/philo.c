/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:32:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/20 11:57:45 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include <string.h>

int	ft_init_mutex(t_pthread *pthread, int num_philo)
{
	int				i;
	pthread_mutex_t	*all_mutex;

	all_mutex = malloc(sizeof(pthread_mutex_t));
	if (all_mutex == NULL)
		return (ft_print_error(ERR_MEM));
	if (pthread_mutex_init(all_mutex, NULL) != 0)
		return (ft_print_error(ERR_MUTEX));
	i = -1;
	while (++i < num_philo)
	{
		if (pthread_mutex_init(&pthread[i].fork_lock, NULL) != 0)
			return (ft_print_error(ERR_MUTEX));
		pthread[i].all_lock = all_mutex;
	}
	return (0);
}

int	ft_check_sim_end(t_pthread *pthread)
{
	int			i;
	int			num_meals;
	long int	timestamp;

	while (1)
	{
		i = -1;
		num_meals = 0;
		if (ft_get_time(&timestamp) == 1)
			return (1);
		timestamp = timestamp - pthread->args.start_tv_usec;
		while (++i < pthread->args.num_philo)
		{
			num_meals += pthread[i].philo.eat_counter;
			if (num_meals == pthread->args.max_meals * pthread->args.num_philo)
				return (0);
			if (timestamp / 1000 - pthread[i].philo.start_time
				> pthread->args.time_to_die)
				return (ft_die_sequence(&pthread[i], &timestamp));
		}
		if (ft_usleep_usec(5000) != 0)
			return (1);
	}
	return (1);
}

int	ft_clean_exit_error(t_pthread *pthread, int destroy_mutex)
{
	if (destroy_mutex == 1)
		ft_destroy_mutex(pthread);
	free(pthread->all_lock);
	free(pthread);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_pthread		*pthread;

	if (ft_parse_and_allocate(argc, argv, &pthread) != 0)
		return (1);
	if (ft_init_mutex(pthread, pthread->args.num_philo) != 0)
		return (ft_clean_exit_error(pthread, 0));
	if (ft_create_thread(pthread) != 0)
		return (ft_clean_exit_error(pthread, 1));
	if (ft_check_sim_end(pthread) != 0)
		return (ft_clean_exit_error(pthread, 1));
	if (ft_join_pthread(pthread) != 0)
		return (ft_clean_exit_error(pthread, 1));
	if (ft_destroy_mutex(pthread) != 0)
		return (ft_clean_exit_error(pthread, 0));
	free(pthread->all_lock);
	free(pthread);
	return (0);
}

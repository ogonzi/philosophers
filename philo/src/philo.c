/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:32:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/20 09:54:38 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include <string.h>

int	ft_set_args(int argc, char *argv[], t_args *args)
{
	args->num_philo = ft_atoi_mod(argv[1]);
	if (args->num_philo == -1)
		return (1);
	args->time_to_die = ft_atoi_mod(argv[2]);
	if (args->time_to_die == -1)
		return (1);
	args->time_to_eat = ft_atoi_mod(argv[3]);
	if (args->time_to_eat == -1)
		return (1);
	args->time_to_sleep = ft_atoi_mod(argv[4]);
	if (args->time_to_sleep == -1)
		return (1);
	if (argc == 6)
	{
		args->max_meals = ft_atoi_mod(argv[5]);
		if (args->max_meals == -1)
			return (1);
	}
	else
		args->max_meals = -1;
	return (0);
}

int	ft_parse_and_allocate(int argc, char *argv[], t_pthread **pthread)
{
	int		i;
	t_args	args;

	if (argc < 5 || argc > 6)
	{
		ft_print_error(ERR_NUM_ARGS);
		return (1);
	}
	if (ft_set_args(argc, argv, &args) == 1)
	{
		ft_print_error(ERR_FORM_ARGS);
		return (1);
	}
	if (ft_allocate_pthread(pthread, args.num_philo) == 1)
	{
		ft_print_error(ERR_MEM);
		return (1);
	}
	i = -1;
	while (++i < args.num_philo)
		(*pthread)[i].args = args;
	return (0);
}

int	ft_init_mutex(t_pthread *pthread, int num_philo)
{
	int				i;
	pthread_mutex_t	*all_mutex;

	all_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(all_mutex, NULL) != 0)
	{
		ft_print_error(ERR_MUTEX);
		return (1);
	}
	i = -1;
	while (++i < num_philo)
	{
		if (pthread_mutex_init(&pthread[i].fork_lock, NULL) != 0)
		{
			ft_print_error(ERR_MUTEX);
			return (1);
		}
		pthread[i].all_lock = all_mutex;
	}
	return (0);
}

int	ft_create_thread(t_pthread *pthread)
{
	int			i;
	long int	start_time;

	i = -1;
	if (ft_get_time(&start_time) == 1)
		return (1);
	memset(&pthread->philo, 0, sizeof(t_philo));
	while (++i < pthread->args.num_philo)
	{
		pthread[i].philo.philo_num = i;
		pthread[i].args.start_tv_usec = start_time;
		if (pthread_create(&(pthread[i].tid), NULL,
				ft_thread_routine, &pthread[i]) != 0)
		{
			ft_print_error(ERR_THREAD);
			return (1);
		}
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
			{
				ft_die_sequence(&pthread[i], &timestamp);
				return (0);
			}
		}
		if (ft_usleep_usec(5000) != 0)
			return (1);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_pthread		*pthread;

	if (ft_parse_and_allocate(argc, argv, &pthread) == 1)
		return (1);
	if (ft_init_mutex(pthread, pthread[0].args.num_philo) == 1)
	{
		free(pthread);
		return (1);
	}
	if (ft_create_thread(pthread) == 1)
	{
		ft_destroy_mutex(pthread);
		free(pthread);
		return (1);
	}
	if (ft_check_sim_end(pthread) != 0)
		return (1);
	ft_join_pthread(pthread);
	ft_destroy_mutex(pthread);
	free(pthread);
	return (0);
}

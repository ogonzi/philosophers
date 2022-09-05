/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:32:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/05 11:41:58 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"

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

int	ft_parse_and_allocate(int argc, char *argv[], t_pthread *pthread)
{
	if (argc < 5 || argc > 6)
	{
		ft_print_error(ERR_NUM_ARGS);
		return (1);
	}
	if (ft_set_args(argc, argv, &(pthread->args)) == 1)
	{
		ft_print_error(ERR_FORM_ARGS);
		return (1);
	}
	if (ft_allocate_pthread(pthread, pthread->args.num_philo) == 1)
	{
		ft_print_error(ERR_MEM);
		return (1);
	}
	return (0);
}

int	ft_init_mutex(t_pthread *pthread, int num_philo)
{
	int	i;
	
	i = -1;
	while (++i < num_philo)
	{
		if (pthread_mutex_init(&(pthread->lock[i]), NULL) != 0)
		{
			ft_print_error(ERR_MUTEX);
			return (1);
		}
	}
	return (0);
}

int	ft_create_thread(t_pthread *pthread)
{
	int	i;

	i = -1;
	while (++i < pthread->args.num_philo)
	{
		if (pthread_create(&(pthread->tid[i]), NULL, ft_thread_routine, pthread) != 0)
		{
			ft_print_error(ERR_THREAD);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_pthread		pthread;
	int				i;

	if (ft_parse_and_allocate(argc, argv, &pthread) == 1)
		return (1);
	if (ft_init_mutex(&pthread, pthread.args.num_philo) == 1)
		return (1);
	if (ft_create_thread(&pthread) == 1)
		return (1);
	i = -1;
	while (++i < pthread.args.num_philo)
		pthread_join(pthread.tid[i], NULL);
	ft_free_pthread(&pthread);
	return (0);
}

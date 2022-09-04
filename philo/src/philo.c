/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:32:51 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/04 19:43:02 by ogonzale         ###   ########.fr       */
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

int	ft_parse_and_allocate(int argc, char *argv[], t_args *args,
		t_pthread *pthread)
{
	if (argc < 5 || argc > 6)
	{
		ft_print_error(ERR_NUM_ARGS);
		return (1);
	}
	if (ft_set_args(argc, argv, args) == 1)
	{
		ft_print_error(ERR_FORM_ARGS);
		return (1);
	}
	if (ft_allocate_pthread(pthread, args->num_philo) == 1)
	{
		ft_print_error(ERR_MEM);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			args;
	t_pthread		pthread;

	if (ft_parse_and_allocate(argc, argv, &args, &pthread) == 1)
		return (1);
	ft_free_pthread(&pthread);
	return (0);
}

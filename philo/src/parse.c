/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:35:10 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/01 13:18:09 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

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
	int		*end;

	if (argc < 5 || argc > 6)
		return (ft_print_error(ERR_NUM_ARGS));
	if (ft_set_args(argc, argv, &args) != 0)
		return (ft_print_error(ERR_FORM_ARGS));
	if (ft_allocate_pthread(pthread, args.num_philo) != 0)
		return (1);
	end = malloc(sizeof(int));
	i = -1;
	while (++i < args.num_philo)
	{
		(*pthread)[i].args = args;
		(*pthread)[i].end = end;
	}
	return (0);
}

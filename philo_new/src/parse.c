/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:35:10 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/02 16:51:47 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"
#include <stdlib.h>

int	ft_set_data(int argc, char *argv[], t_data *data)
{
	data->num_philos = ft_atoi_mod(argv[1]);
	if (data->num_philos == -1)
		return (1);
	data->time_to_die = ft_atoi_mod(argv[2]);
	if (data->time_to_die == -1)
		return (1);
	data->time_to_eat = ft_atoi_mod(argv[3]);
	if (data->time_to_eat == -1)
		return (1);
	data->time_to_sleep = ft_atoi_mod(argv[4]);
	if (data->time_to_sleep == -1)
		return (1);
	if (argc == 6)
	{
		data->max_meals = ft_atoi_mod(argv[5]);
		if (data->max_meals == -1)
			return (1);
	}
	else
		data->max_meals = -1;
	return (0);
}

int	ft_parse(int argc, char *argv[], t_data *data)
{
	if (argc < 5 || argc > 6)
		return (ft_print_error(ERR_NUM_ARGS));
	if (ft_set_data(argc, argv, data) != 0)
		return (ft_print_error(ERR_FORM_ARGS));
	return (0);
}

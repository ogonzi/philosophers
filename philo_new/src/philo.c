/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:10:25 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/04 18:28:54 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_print_error(ERR_MEM));
	if (ft_parse(argc, argv, data) != 0)
		return (1);
	if (ft_init_mutexes(data) != 0)
		return (ft_cleanup(data, 0, 1));
	if (ft_init_philosophers(data) != 0)
		return (ft_cleanup(data, 1, 1));
	data->start_time = ft_get_time();
	if (data->start_time == -1)
		return (ft_cleanup(data, 1, 1));
	if (ft_create_pthreads(data) != 0)
		return (ft_cleanup(data, 1, 1));
	return (ft_cleanup(data, 1, 0));
}

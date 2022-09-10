/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:14:04 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/10 17:25:10 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

int	ft_usleep_ms(int sleep_ms)
{
	if (usleep(sleep_ms) == -1)
	{
		ft_print_error(ERR_USLEEP);
		return (1);
	}
	return (0);
}

void	ft_die_sequence(t_pthread *pthread, long int *timestamp)
{
	if (ft_usleep_ms(pthread->args.time_to_die * 1000) == 1)
		return ;
	if (ft_get_time(timestamp) == 1)
		return ;
	*timestamp = *timestamp - pthread->args.start_tv_msec;
	ft_print_state_change(*timestamp, pthread->philo.philo_num + 1, DIE_CODE);
}

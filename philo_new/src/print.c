/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:24 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/03 16:58:10 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

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

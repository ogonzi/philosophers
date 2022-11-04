/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:48:24 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/04 16:46:59 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

void	ft_print_state_change(long long int timestamp, int philo_num,
			int state_code)
{
	if (state_code == FORK_CODE)
		printf("%lld %d has taken a fork\n", timestamp, philo_num);
	if (state_code == EAT_CODE)
		printf("%lld %d is eating\n", timestamp, philo_num);
	if (state_code == SLEEP_CODE)
		printf("%lld %d is sleeping\n", timestamp, philo_num);
	if (state_code == THINK_CODE)
		printf("%lld %d is thinking\n", timestamp, philo_num);
	if (state_code == DIE_CODE)
		printf("%lld %d died\n", timestamp, philo_num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:02:53 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/09 11:41:56 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

void	*ft_thread_routine(void *pthread)
{
	struct timeval	time;
	t_pthread		*this_pthread;

	this_pthread = (t_pthread *)pthread;
	printf("Philo: %d\n", this_pthread->philo.philo_num);
	if (this_pthread->philo.philo_num % 2 == 1)
		usleep(100000);
	gettimeofday(&time, NULL);
	printf("Job executed at %ld\n", time.tv_usec / 1000);
	return (0);
}

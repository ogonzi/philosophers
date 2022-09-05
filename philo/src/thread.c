/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:02:53 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/05 11:39:35 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

void	*ft_thread_routine(void *pthread)
{
	struct timeval	time;
	t_pthread		*this_pthread;

	this_pthread = (t_pthread *)pthread;
	gettimeofday(&time, NULL);
	printf("Job executed at %ld\n", time.tv_usec / 1000);
	printf("Number of philosophers: %d\n", this_pthread->args.num_philo);
	return (0);
}

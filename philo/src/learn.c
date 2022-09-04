/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:15:50 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/04 11:32:46 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> 

pthread_mutex_t	lock;

void	*work_func(void *counter)
{
	unsigned long	i;
	int				*this_counter;
	struct timeval	time;

	this_counter = (int *)counter;
	pthread_mutex_lock(&lock);
	i = 0;
	*this_counter += 1;
	gettimeofday(&time, NULL);
	printf("Job %d started at %ld\n", *this_counter, time.tv_usec);
	while (++i < 0xFFFFFFFF);
	gettimeofday(&time, NULL);
	printf("Job %d finished at %ld\n", *this_counter, time.tv_usec);
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int	main(void)
{
	pthread_t		tid[2];
	int				counter;
	int				i;
	int				err;

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		return (1);
	}
	counter = 0;
	i = 0;
	while (i < 2)
	{
		err = pthread_create(&(tid[i]), NULL, work_func, &counter);
		if (err != 0)
			printf("Can't create thread: [%s]\n", strerror(err));
		i++;
	}
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_mutex_destroy(&lock);
	return (0);
}

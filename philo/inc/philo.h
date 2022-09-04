/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:54:02 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/04 18:58:03 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_args
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meals;
}		t_args;

typedef struct s_pthread
{
	pthread_t		*tid;
	pthread_mutex_t	*lock;
}					t_pthread;

/* ft_atoi_mod.c */

int	ft_atoi_mod(const char *nptr);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:54:02 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/20 08:56:52 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_args
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	long int	start_tv_usec;
}				t_args;

typedef struct s_philo
{
	int			eating;
	int			sleeping;
	int			thinking;
	int			forks_used;
	int			died;
	int			eat_counter;
	long int	start_time;
	int			philo_num;
}				t_philo;

typedef struct s_pthread
{
	pthread_t		tid;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	*all_lock;
	t_args			args;
	t_philo			philo;
}					t_pthread;

/* ft_atoi_mod.c */

int		ft_atoi_mod(const char *nptr);

/* thread.c */

void	*ft_thread_routine(void *args);
int		ft_philo_will_die(t_pthread *pthread);

/* activity.c */

int		ft_eat(t_pthread *this_pthread, t_pthread *left_pthread, long int *t);
int		ft_sleep(t_pthread *this_pthread, long int *t);
int		ft_think(t_pthread *this_pthread, long int *t);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:58:55 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/04 17:12:34 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				philo_num;
	int				right_fork;
	int				left_fork;
	long long int	last_meal;
	int				num_meals;
	long long int	time_of_start;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int					num_philos;
	long long int		time_to_die;
	long long int		time_to_eat;
	long long int		time_to_sleep;
	long long int		max_meals;
	int					death;
	long long int		start_time;
	long long int		current_time;
	int					err;
	t_philo				*philo;
	pthread_mutex_t		m_death;
	pthread_mutex_t		*m_fork;
	pthread_mutex_t		m_print;
}						t_data;

/* parse.c */

int		ft_parse(int argc, char *argv[], t_data *data);

/* init.c */

int		ft_init_mutexes(t_data *data);
int		ft_init_philosophers(t_data *data);

/* create_pthreads.c */

int		ft_create_pthreads(t_data *data);

/* print.c */

void	ft_print_state_change(long long int timestamp, int philo_num,
			int state_code);

/* activities.c */

int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);

/* end_conditions.c */

int		ft_routine_is_finished(t_data *data);
int		ft_any_philo_died(t_data *data);

#endif

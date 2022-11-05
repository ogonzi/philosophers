/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:58:55 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/05 13:40:16 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				number;
	int				right_fork_index;
	int				left_fork_index;
	long long int	time_of_last_meal;
	int				meal_counter;
	long long int	time_of_start;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int					number_of_philos;
	long long int		time_to_die;
	long long int		time_to_eat;
	long long int		time_to_sleep;
	long long int		max_meals;
	int					death;
	long long int		start_time;
	long long int		current_time;
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

int		ft_print_state_change(t_philo *philo, int state);

/* activities.c */

int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);

/* end_conditions.c */

int		ft_routine_is_finished(t_data *data);
int		ft_any_philo_died(t_data *data);

#endif

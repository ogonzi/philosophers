/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:58:55 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/03 16:40:01 by ogonzale         ###   ########.fr       */
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
	int				needs_to_eat;
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
	long long int		time_absolute;
	long long int		time_relative;
	t_philo				*philo;
	pthread_mutex_t		m_death;
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		m_print;
}						t_data;

/* parse.c */

int	ft_parse(int argc, char *argv[], t_data *data);

/* ft_atoi_mod.c */

long long int	ft_atoi_mod(const char *nptr);

#endif

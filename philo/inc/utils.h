/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:29:13 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/10 12:36:09 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

# define ERR_NUM_ARGS	"The number of arguments is not correct"
# define ERR_FORM_ARGS	"One or more arguments are not correctly formated"
# define ERR_MEM		"Memory allocation failed"
# define ERR_MUTEX		"Mutex initialization failed"
# define ERR_THREAD		"Thread creation failed"
# define ERR_TIME		"Get time of day failed"

# define FORK_CODE	0
# define EAT_CODE	1
# define SLEEP_CODE	2
# define THINK_CODE	3
# define DIE_CODE	4

/* utils.c */

void	ft_print_error(char *s);
void	ft_print_state_change(int timestamp, int philo_num,
			int state_code);
int		ft_allocate_pthread(t_pthread **pthread, int philo_num);
int		ft_get_time(long int *time);
#endif

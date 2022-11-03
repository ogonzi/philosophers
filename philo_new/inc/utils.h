/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:29:13 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/03 16:21:13 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

# define ERR_NUM_ARGS		"The number of arguments is not correct"
# define ERR_FORM_ARGS		"One or more arguments are not correctly formated"
# define ERR_MEM			"Memory allocation failed"
# define ERR_MUTEX			"Mutex initialization failed"
# define ERR_THREAD			"Thread creation failed"
# define ERR_TIME			"Get time of day failed"
# define ERR_USLEEP			"Usleep failed"
# define ERR_MUTEX_LOCK		"Mutex lock failed"
# define ERR_MUTEX_UNLOCK	"Mutex unlock failed"
# define ERR_JOIN			"Pthread join failed"
# define ERR_MUTEX_DESTROY	"Mutex destroy failed"
# define ERR_DETACH			"Pthread detach failed"

# define FORK_CODE	0
# define EAT_CODE	1
# define SLEEP_CODE	2
# define THINK_CODE	3
# define DIE_CODE	4

/* utils.c */

int		ft_strlen(const char *s);
int		ft_print_error(char *s);
void	ft_print_state_change(int timestamp, int philo_num, int state_code);
int		ft_get_time(long int *time);

/* utils_2.c */

#endif

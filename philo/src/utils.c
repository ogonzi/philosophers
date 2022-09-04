/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:24:29 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/04 12:34:50 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	ft_print_error(char *s)
{
	if (write(2, "Error: ", 7) == -1)
		return ;
	if (s)
	{
		if (write(2, s, ft_strlen(s)) == -1)
			return ;
	}
	if (write(2, "\n", 1) == -1)
		return ;
}

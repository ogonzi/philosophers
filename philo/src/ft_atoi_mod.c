/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 09:47:30 by ogonzale          #+#    #+#             */
/*   Updated: 2022/09/04 12:35:36 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_check_empty(const char *nptr, int *i)
{
	while ((nptr[*i] >= '\t' && nptr[*i] <= '\r') || nptr[*i] == ' '
			|| nptr[*i] == '\0')
	{
		if (nptr[*i] == '\0')
			return (1);
		(*i)++;
	}
	return (0);
}

int	ft_check_sign(const char *nptr, int *i)
{
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			return (1);
		(*i)++;
	}
	return (0);
}

int	ft_check_digit(const char *nptr, int *i)
{
	while (nptr[*i] != '\0')
	{
		if (nptr[*i] < '0' || nptr[*i] > '9')
			return (1);
		(*i)++;
	}
	return (0);
}

int	ft_pow(int n, unsigned int pow)
{
	if (pow == 0)
		return (1);
	return (n * ft_pow(n, pow - 1));
}

int	ft_atoi_mod(const char *nptr)
{
	int		i;
	long	res;
	int		start_num;

	i = 0;
	res = 0;
	if (ft_check_empty(nptr, &i) == 1)
		return (-1);
	if (ft_check_sign(nptr, &i) == 1)
		return (-1);
	start_num = i - 1;
	if (ft_check_digit(nptr, &i) == 1)
		return (-1);
	while (++start_num < i)
		res = res + (nptr[start_num] - '0') * ft_pow(10, i - start_num - 1);
	if (res > 2147483647)
		return (-1);
	return ((int)res);
}

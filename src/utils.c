/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:08:08 by xchalle           #+#    #+#             */
/*   Updated: 2021/12/03 10:27:42 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	ft_atoi(const char *str, int i, long long d, int c)
{
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			c *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		d = d * 10 + (str[i] - 48);
		i++;
		if ((d > 0 && c == -1) || (d > 2147483647 && c == 1))
			return (2147483648);
	}
	return (d * c);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_arg(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_num(argv[i]) == 0)
			return (-1);
		if (ft_atoi(argv[i], 0, 0, 1) == 2147483648)
			return (-1);
		i++;
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	t;
	long long		time;

	time = 0;
	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

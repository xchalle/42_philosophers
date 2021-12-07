/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:48:44 by xchalle           #+#    #+#             */
/*   Updated: 2021/12/07 18:09:08 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	mut_ini(t_p *phil)
{
	pthread_mutex_init(&phil->gbl.diemut, NULL);
	pthread_mutex_init(&phil->gbl.clomut, NULL);
	pthread_mutex_init(&phil->gbl.eatmut, NULL);
	pthread_mutex_init(&phil->gbl.nbrmut, NULL);
	pthread_mutex_init(&phil->gbl.printer_mutex, NULL);
}

void	mut_dest(t_p *phil)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&phil->gbl.diemut);
	pthread_mutex_destroy(&phil->gbl.clomut);
	pthread_mutex_destroy(&phil->gbl.eatmut);
	pthread_mutex_destroy(&phil->gbl.nbrmut);
	pthread_mutex_destroy(&phil->gbl.printer_mutex);
	while (i < phil->gbl.nuph)
	{
		pthread_mutex_destroy(&phil->fork[i]);
		i++;
	}
	free(phil->fork);
	free(phil->user);
	free(phil);
}

void	printer(t_user *user, char *str, int i)
{
	pthread_mutex_lock(&user->gbl->printer_mutex);
	pthread_mutex_lock(&user->gbl->clomut);
	if (*user->close == 0 && i != 1)
	{
		pthread_mutex_unlock(&user->gbl->clomut);
		pthread_mutex_unlock(&user->gbl->printer_mutex);
		return ;
	}
	pthread_mutex_unlock(&user->gbl->clomut);
	printf("%lld %d %s", get_time() - user->crea_time, (user->left_f + 1), str);
	if (ft_strlen(str) != 5)
		pthread_mutex_unlock(&user->gbl->printer_mutex);
	else
	{
		pthread_mutex_unlock(&user->gbl->printer_mutex);
		pthread_mutex_lock(&user->gbl->clomut);
		*user->close = 0;
		pthread_mutex_unlock(&user->gbl->clomut);
	}
	return ;
}

void	init_var(t_p *phil, char **argv)
{
	phil->gbl.nbr_died = 0;
	phil->gbl.done_eat = 0;
	phil->gbl.nuph = ft_atoi(argv[1], 0, 0, 1);
	phil->gbl.tidie = ft_atoi(argv[2], 0, 0, 1);
	phil->gbl.tieat = ft_atoi(argv[3], 0, 0, 1);
	phil->gbl.tisle = ft_atoi(argv[4], 0, 0, 1);
}

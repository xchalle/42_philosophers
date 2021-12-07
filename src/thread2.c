/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:56:37 by xchalle           #+#    #+#             */
/*   Updated: 2021/12/06 10:59:09 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat_checking(t_user *user_t)
{
	pthread_mutex_lock(&user_t->gbl->eatmut);
	if (get_time()
		- user_t->last_eat >= user_t->gbl->tidie)
	{
		user_t->gbl->nbr_died++;
		pthread_mutex_lock(&user_t->gbl->clomut);
		*user_t->close = 0;
		pthread_mutex_unlock(&user_t->gbl->clomut);
		if (user_t->gbl->nbr_died == 1)
			printer(user_t, "died\n", 1);
		user_t->alive = 0;
	}
	pthread_mutex_unlock(&user_t->gbl->eatmut);
}

void	check_nbr(t_user *user_t)
{
	pthread_mutex_lock(&user_t->gbl->nbrmut);
	if (user_t->nbr_eat == user_t->gbl->nueat && user_t->only_once == 1)
	{
		pthread_mutex_unlock(&user_t->gbl->diemut);
		user_t->gbl->done_eat++;
		user_t->only_once = 0;
		pthread_mutex_unlock(&user_t->gbl->diemut);
	}
	pthread_mutex_unlock(&user_t->gbl->nbrmut);
	if (user_t->gbl->done_eat == user_t->gbl->nuph)
	{
		pthread_mutex_lock(&user_t->gbl->clomut);
		*user_t->close = 0;
		pthread_mutex_unlock(&user_t->gbl->clomut);
		user_t->alive = 0;
	}
}

void	*kekw(void *user)
{
	t_user	*user_t;

	user_t = (t_user *)user;
	pthread_mutex_lock(&user_t->gbl->clomut);
	while (*user_t->close == 1)
	{
		pthread_mutex_unlock(&user_t->gbl->clomut);
		eat_checking(user_t);
		check_nbr(user_t);
		usleep(100);
		pthread_mutex_lock(&user_t->gbl->clomut);
	}
	*user_t->close = 0;
	pthread_mutex_unlock(&user_t->gbl->clomut);
	return (NULL);
}

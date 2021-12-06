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
	if (user_t->eating == 0 && get_time()
		- user_t->last_eat >= user_t->gbl->tidie)
	{
		pthread_mutex_lock(&user_t->eatmut);
		user_t->gbl->nbr_died++;
		if (user_t->gbl->nbr_died == 1)
			printer(user_t, "died\n");
		*user_t->close = 0;
		user_t->alive = 0;
		pthread_mutex_unlock(&user_t->eatmut);
	}
}

void	*kekw(void *user)
{
	t_user	*user_t;

	user_t = (t_user *)user;
	while (*user_t->close == 1)
	{
		eat_checking(user_t);
		if (user_t->nbr_eat == user_t->gbl->nueat && user_t->only_once == 1)
		{
			pthread_mutex_lock(&user_t->diemut);
			user_t->gbl->done_eat++;
			user_t->only_once = 0;
			pthread_mutex_unlock(&user_t->diemut);
		}
		if (user_t->gbl->done_eat == user_t->gbl->nuph)
		{
			*user_t->close = 0;
			user_t->alive = 0;
		}
		usleep(100);
	}
	*user_t->close = 0;
	return (NULL);
}

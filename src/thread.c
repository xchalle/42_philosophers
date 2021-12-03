/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:31:04 by xchalle           #+#    #+#             */
/*   Updated: 2021/12/03 10:38:54 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printer(t_user *user, char *str)
{
	pthread_mutex_lock(&user->printer_mutex);
	if (*user->close == 0)
	{
		pthread_mutex_unlock(&user->printer_mutex);
		return ;
	}
	printf("%lld %d %s", get_time() - user->crea_time, (user->left_f + 1), str);
	if (ft_strlen(str) != 5)
		pthread_mutex_unlock(&user->printer_mutex);
	else
	{
		*user->close = 0;
		pthread_mutex_unlock(&user->printer_mutex);
	}
	return ;
}

void	sleeping(t_user *user_t)
{
	if (*user_t->close == 0)
		return ;
	printer(user_t, "is sleeping\n");
	user_t->last_sleep = get_time();
	usleep(user_t->gbl->tisle * 1000);
}

void	think(t_user *user_t)
{
	if (*user_t->close == 0)
		return ;
	printer(user_t, "is thinking\n");
}

void	eat(t_user *user_t)
{
	pthread_mutex_lock(&user_t->fork[user_t->left_f]);
	printer(user_t, "has taken a fork left\n");
	pthread_mutex_lock(&user_t->fork[user_t->right_f]);
	printer(user_t, "has taken a fork right\n");
	pthread_mutex_lock(&user_t->eatmut);
	user_t->eating = 1;
	printer(user_t, "is eating\n");
	user_t->last_eat = get_time();
	user_t->nbr_eat++;
	usleep(user_t->gbl->tieat * 1000);
	user_t->eating = 0;
	pthread_mutex_unlock(&user_t->eatmut);
	pthread_mutex_unlock(&user_t->fork[user_t->left_f]);
	pthread_mutex_unlock(&user_t->fork[user_t->right_f]);
}

void	*routine(void *user)
{
	t_user	*user_t;

	user_t = (t_user *)user;
	while (*user_t->close == 1)
	{
		if (user_t->gbl->nuph == 1)
			return (NULL);
		eat(user_t);
		sleeping(user_t);
		think(user_t);
		usleep(100);
	}
	return (NULL);
}

void	*kekw(void *user)
{
	t_user	*user_t;

	user_t = (t_user *)user;
	while (*user_t->close == 1)
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

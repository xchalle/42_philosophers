/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:31:04 by xchalle           #+#    #+#             */
/*   Updated: 2021/12/06 11:20:52 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	sleeping(t_user *user_t)
{
	pthread_mutex_lock(&user_t->gbl->clomut);
	if (*user_t->close == 0)
	{
		pthread_mutex_unlock(&user_t->gbl->clomut);
		return ;
	}
	pthread_mutex_unlock(&user_t->gbl->clomut);
	printer(user_t, "is sleeping\n", 0);
	user_t->last_sleep = get_time();
	usleep(user_t->gbl->tisle * 1000);
}

void	think(t_user *user_t)
{
	pthread_mutex_lock(&user_t->gbl->clomut);
	if (*user_t->close == 0)
	{
		pthread_mutex_unlock(&user_t->gbl->clomut);
		return ;
	}
	pthread_mutex_unlock(&user_t->gbl->clomut);
	printer(user_t, "is thinking\n", 0);
}

void	eat_odd(t_user *user_t)
{
	pthread_mutex_lock(&user_t->fork[user_t->right_f]);
	printer(user_t, "has taken a fork right\n", 0);
	pthread_mutex_lock(&user_t->fork[user_t->left_f]);
	printer(user_t, "has taken a fork left\n", 0);
	printer(user_t, "is eating\n", 0);
	pthread_mutex_lock(&user_t->gbl->eatmut);
	user_t->last_eat = get_time();
	pthread_mutex_unlock(&user_t->gbl->eatmut);
	pthread_mutex_lock(&user_t->gbl->nbrmut);
	user_t->nbr_eat++;
	pthread_mutex_unlock(&user_t->gbl->nbrmut);
	usleep(user_t->gbl->tieat * 1000);
	pthread_mutex_unlock(&user_t->fork[user_t->right_f]);
	pthread_mutex_unlock(&user_t->fork[user_t->left_f]);
}

void	eat_even(t_user *user_t)
{
	pthread_mutex_lock(&user_t->fork[user_t->left_f]);
	printer(user_t, "has taken a fork left\n", 0);
	pthread_mutex_lock(&user_t->fork[user_t->right_f]);
	printer(user_t, "has taken a fork right\n", 0);
	printer(user_t, "is eating\n", 0);
	pthread_mutex_lock(&user_t->gbl->eatmut);
	user_t->last_eat = get_time();
	pthread_mutex_unlock(&user_t->gbl->eatmut);
	pthread_mutex_lock(&user_t->gbl->nbrmut);
	user_t->nbr_eat++;
	pthread_mutex_unlock(&user_t->gbl->nbrmut);
	usleep(user_t->gbl->tieat * 1000);
	pthread_mutex_unlock(&user_t->fork[user_t->left_f]);
	pthread_mutex_unlock(&user_t->fork[user_t->right_f]);
}

void	*routine(void *user)
{
	t_user	*user_t;

	user_t = (t_user *)user;
	pthread_mutex_lock(&user_t->gbl->clomut);
	while (*user_t->close == 1)
	{
		pthread_mutex_unlock(&user_t->gbl->clomut);
		if (user_t->gbl->nuph == 1)
			return (NULL);
		if ((user_t->left_f % 2) == 1)
			eat_even(user_t);
		if ((user_t->left_f % 2) == 0)
			eat_odd(user_t);
		sleeping(user_t);
		think(user_t);
		usleep(100);
		pthread_mutex_lock(&user_t->gbl->clomut);
	}
	pthread_mutex_unlock(&user_t->gbl->clomut);
	return (NULL);
}

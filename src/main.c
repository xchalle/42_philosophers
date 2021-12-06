/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:46:26 by xchalle           #+#    #+#             */
/*   Updated: 2021/12/06 10:45:59 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_p	*initiate_user(t_p *phil, char **argv, int *close_n)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1], 0, 0, 1))
	{
		phil->user[i].gbl = &phil->gbl;
		phil->user[i].fork = phil->fork;
		phil->user[i].alive = 1;
		phil->user[i].left_f = i;
		phil->user[i].right_f = (i + 1) % ft_atoi(argv[1], 0, 0, 1);
		phil->user[i].crea_time = phil->creat_time;
		phil->user[i].eat_time = 0;
		phil->user[i].eating = 0;
		phil->user[i].close = close_n;
		phil->user[i].nbr_eat = 0;
		phil->user[i].sleep_time = 0;
		phil->user[i].sleeping = 0;
		phil->user[i].think_time = 0;
		phil->user[i].thinking = 0;
		phil->user[i].only_once = 1;
		pthread_mutex_init(&phil->fork[i], NULL);
		i++;
	}
	return (phil);
}

t_p	*initiate_global(t_p *phil, char **argv, int argc, int *close_n)
{
	phil->gbl.nbr_died = 0;
	phil->gbl.nuph = ft_atoi(argv[1], 0, 0, 1);
	phil->gbl.tidie = ft_atoi(argv[2], 0, 0, 1);
	phil->gbl.tieat = ft_atoi(argv[3], 0, 0, 1);
	phil->gbl.tisle = ft_atoi(argv[4], 0, 0, 1);
	if (argc == 6)
		phil->gbl.nueat = ft_atoi(argv[5], 0, 0, 1);
	else
		phil->gbl.nueat = -1;
	phil->creat_time = get_time();
	phil->fork = malloc(sizeof(pthread_mutex_t)
			* (ft_atoi(argv[1], 0, 0, 1) + 1));
	if (phil->fork == NULL)
		return (NULL);
	phil->user = malloc(sizeof(t_user)
			* (ft_atoi(argv[1], 0, 0, 1) + 1));
	if (phil->user == NULL)
		return (NULL);
	phil = initiate_user(phil, argv, close_n);
	return (phil);
}

void	loop_thread(t_p *phil)
{
	int	i;

	i = 0;
	while (i < phil->gbl.nuph)
	{
		phil->user[i].last_eat = get_time();
		pthread_create(&phil->user[i].thread, NULL,
			&routine, (void *)&phil->user[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < phil->gbl.nuph)
	{
		pthread_create(&phil->user[i].thread_2, NULL,
			&kekw, (void *)&phil->user[i]);
		usleep(100);
		i++;
	}
}

void	start_philo(t_p *phil)
{
	int	i;

	i = 0;
	loop_thread(phil);
	while (i < phil->gbl.nuph)
	{
		pthread_join(phil->user[i].thread_2, NULL);
		pthread_join(phil->user[i].thread, NULL);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_p	*phil;
	int	close_n;

	close_n = 1;
	if (argc < 5 || argc > 6)
	{
		printf("philo: 4 or 5 arguments needed\n");
		return (-1);
	}
	if ((check_arg(argv, argc)) == -1)
	{
		printf("unvalid arguments\n");
		return (-1);
	}
	phil = malloc(sizeof(t_p));
	if (phil == NULL)
		return (0);
	phil = initiate_global(phil, argv, argc, &close_n);
	if (phil == NULL)
		return (0);
	start_philo(phil);
	free(phil->fork);
	free(phil->user);
	free (phil);
	return (0);
}

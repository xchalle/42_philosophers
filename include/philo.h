/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchalle <xchalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:32:48 by xchalle           #+#    #+#             */
/*   Updated: 2021/12/07 16:50:39 by xchalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_global
{
	int				nuph;
	int				tidie;
	int				tieat;
	int				tisle;
	int				nueat;
	int				nbr_died;
	int				nbr_eat;
	int				done_eat;
	pthread_mutex_t	diemut;
	pthread_mutex_t	nbrmut;
	pthread_mutex_t	clomut;
	pthread_mutex_t	eatmut;
	pthread_mutex_t	printer_mutex;
}		t_global;

typedef struct s_user
{
	pthread_t		thread;
	pthread_t		thread_2;	
	pthread_mutex_t	*fork;
	t_global		*gbl;
	int				left_f;
	int				right_f;
	int				sleeping;
	int				eating;
	int				thinking;
	long long		crea_time;
	long long		last_sleep;
	long long		last_eat;
	int				*close;
	int				sleep_time;
	int				think_time;
	int				eat_time;
	int				nbr_eat;
	int				alive;
	int				only_once;
}		t_user;

typedef struct s_p
{
	t_global		gbl;
	pthread_mutex_t	*fork;
	t_user			*user;
	long long		creat_time;
}		t_p;

int			ft_strlen(char *str);
int			check_arg(char **argv, int argc);
long long	get_time(void);
long long	ft_atoi(const char *str, int i, long long d, int c);
void		*routine(void *user);
void		*kekw(void *user);
void		printer(t_user *user, char *str, int i);
void		mut_dest(t_p *phil);
void		mut_ini(t_p *phil);
void		init_var(t_p *phil, char **argv);

#endif

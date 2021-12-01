#include "../include/philo.h"

void    printer(t_user *user, char *str)
{
    pthread_mutex_lock(&user->printer_mutex);
    if (*user->close == 0)
    {
        printf("%d %lld %d %s", *user->close, get_time() - user->crea_time, user->left_f, str);
        pthread_mutex_unlock(&user->printer_mutex);
        return ;
    }
    printf("%d %lld %d %s", *user->close, get_time() - user->crea_time, user->left_f, str);
    if (ft_strlen(str) != 5)
        pthread_mutex_unlock(&user->printer_mutex);
    else
    {
        *user->close = 0;
        //usleep(100);
        pthread_mutex_unlock(&user->printer_mutex);
    }
    return ;
}

void    sleeping(t_user *user_t)
{
    if (*user_t->close == 0)
        return ;
    printer(user_t, "is sleeping\n");
    usleep(user_t->gbl.tisle);
}

void think(t_user *user_t)
{
    if (*user_t->close == 0)
        return ;
    printer(user_t, "is thinking\n");
}

void    eat(t_user *user_t)
{
    pthread_mutex_lock(&user_t->fork[user_t->left_f]);
    printer(user_t, "has taken a fork\n");
    pthread_mutex_lock(&user_t->fork[user_t->right_f]);
    printer(user_t, "has taken a fork\n");
    pthread_mutex_lock(&user_t->eatmut);
    user_t->eating = 1;
    printer(user_t, "is eating\n");
    user_t->last_eat = get_time();
    user_t->nbr_eat++;
    usleep(user_t->gbl.tieat);
    user_t->eating = 0;
    pthread_mutex_unlock(&user_t->eatmut);
    pthread_mutex_unlock(&user_t->fork[user_t->left_f]);
    pthread_mutex_unlock(&user_t->fork[user_t->right_f]);
}

void    *routine(void *user)
{
    t_user *user_t;

    user_t = (t_user *)user;
    while (*user_t->close == 1)
    {
        if (user_t->gbl.nueat > 0 && user_t->nbr_eat >= user_t->gbl.nueat)
            return (NULL);
        if (*user_t->close == 0)
        {
            user_t->alive = 0;
            return (NULL);
        }
        eat(user_t);
        sleeping(user_t);
        think(user_t);
        usleep(100);
        if (*user_t->close == 0)
        {
            user_t->alive = 0;
            return (NULL);
        }
    }
    return (NULL);
}

void    *kekw(void *user)
 {
    t_user *user_t;
    int i;

    user_t = (t_user *)user;
    i = 0;
    while (*user_t->close == 1)
    {
        if (user_t->eating == 0 && get_time() - user_t->last_eat >= user_t->gbl.tidie)
        {
            pthread_mutex_lock(&user_t->eatmut);
            printer(user_t, "died\n");
            //if (*user_t->close == 1)
            //    printf("%lld philo %d died\n", (get_time() - user_t->crea_time), user_t->left_f);
            *user_t->close = 0;
            user_t->alive = 0;
            pthread_mutex_unlock(&user_t->eatmut);
        }
        if (user_t->nbr_eat == user_t->gbl.nueat)
        {
            user_t->alive = 0;
            return (NULL);
        }
        i++;
        usleep(100);
    }
    //pthread_mutex_unlock(&user_t->printer_mutex);
    *user_t->close = 0;
    return(NULL);
 }
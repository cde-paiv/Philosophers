/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:20:32 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/29 21:06:16 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//obtem o tempo atual em milissegundos
long    get_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

//imprime mensagens sobre o estatdo dos filosofos
void    messages(t_philo *philo, char *text)
{
    long    time;

    time = get_time() - philo->rules->start_time;
    pthread_mutex_lock(&philo->rules->check);
    if (text && philo->rules->status == STILL)
        printf("%ld %d %s", time, philo->id, text);
    pthread_mutex_unlock(&philo->rules->check);
    if (text == NULL)
        printf("%ld all philo are full", time);
}

//pausa a execucao por um tempo especifico
void    ft_sleep(long time)
{
    long    start;

    start = get_time();
    while (get_time() - start < time)
        usleep(500);
}

//verifica se um filosofo morreu ou todos estao cheios alterando
//o status da simulacao se necessario
int check_life(t_philo *philo)
{
    pthread_mutex_lock(&philo->rules->end);
    pthread_mutex_lock(&philo->rules->check);
    if (get_time() - philo->last_meal >= philo->rules->time_die)
    {
        messages(philo, "died\n");
        philo->rules->status = OVER;
        pthread_mutex_unlock(&philo->rules->check);
        pthread_mutex_unlock(&philo->rules->end);
        return (OVER);
    }
    if (philo->rules->meals_num > 0 && philo->num_meals >= philo->rules->meals_num)
    {
        pthread_mutex_lock(&philo->rules->monitor);
        philo->rules->philos_full++;
        if (philo->rules->philo_num == philo->rules->philos_full)
        {
            messages(philo, NULL);
            philo->rules->status = OVER;
            pthread_mutex_unlock(&philo->rules->monitor);
            pthread_mutex_unlock(&philo->rules->check);
            pthread_mutex_unlock(&philo->rules->end);
            return (OVER);
        }
        pthread_mutex_unlock(&philo->rules->monitor);
    }
    pthread_mutex_unlock(&philo->rules->check);
    pthread_mutex_unlock(&philo->rules->end);
    return (STILL);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        messages(philo, "is thinking\n");
        pthread_mutex_lock(philo->r_fork);
        messages(philo, "has taken a fork\n");
        pthread_mutex_lock(philo->l_fork);
        messages(philo, "has taken a fork\n");
        messages(philo, "is eating\n");
        
        philo->last_meal = get_time();
        philo->num_meals++;
        
        usleep(philo->rules->time_eat * 1000);
        
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        
        messages(philo, "is sleeping\n");
        usleep(philo->rules->time_sleep * 1000);
    }
    return NULL;
}

//verifica se a simulacao deve ser interrompida
int check_break(t_philo *philo)
{
    pthread_mutex_lock(&philo->rules->monitor);
    if (philo->rules->status == OVER)
    {
        pthread_mutex_unlock(&philo->rules->monitor);
        return (OVER);
    }
    pthread_mutex_unlock(&philo->rules->monitor);
    return (STILL);
}

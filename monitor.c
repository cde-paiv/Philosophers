/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:48:47 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/28 18:17:32 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    monitor(t_rules *rules, t_philo *philos)
{
    int i;
    int finish;

    finish = STILL;
    while (finish == STILL)
    {
        i = -1;
        while (++i < rules->philo_num)
        {
            if (finish == STILL && check_life(&philos[i]) == OVER)
                finish = OVER;
        }
        usleep(50);
    }
    close_program(rules, philos);
}

int check_life(t_philo *philo)
{
    pthread_mutex_lock(&philo->rules->end);
    pthread_mutex_lock(&philo->rules->check);
    if (get_time() - philo->last_meal >= philo->rules->time_die)
    {
        pthread_mutex_unlock(&philo->rules->check);
        messages(philo, "died\n");
        philo->rules->status = OVER;
        pthread_mutex_unlock(&philo->rules->end);
        return (philo->rules->status);
    }
    if (philo->rules->meals_num > 0
        && philo->num_meals >= philo->rules->meals_num)
    {
        if (philo->rules->philo_num == philo->rules->philos_full)
        {
            pthread_mutex_unlock(&philo->rules->check);
            philo->rules->status = OVER;
            messages(philo, NULL);
            pthread_mutex_unlock(&philo->rules->end);
            return (philo->rules->status);
        }
    }
    pthread_mutex_unlock(&philo->rules->check);
    pthread_mutex_unlock(&philo->rules->end);
    return (STILL);
}
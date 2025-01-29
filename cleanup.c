/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:29:37 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/29 20:27:02 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void mutex_destroyer(t_rules *rules)
{
    int i;

    i = -1;
    while (++i < rules->philo_num)
        pthread_mutex_destroy(&rules->forks[i]);

    pthread_mutex_destroy(&rules->check);
    pthread_mutex_destroy(&rules->write);
    pthread_mutex_destroy(&rules->monitor);
    pthread_mutex_destroy(&rules->end);
    pthread_mutex_destroy(&rules->eat);
    pthread_mutex_destroy(&rules->routine);
}

static void free_all(t_rules *rules, t_philo *philo)
{
    if (rules->forks)
    {
        free(rules->forks);
        rules->forks = NULL;
    }
    if (philo)
    {
        free(philo);
        philo = NULL;
    }
}

void join_threads(t_rules *rules, t_philo *philo)
{
    int i;

    if (!philo)
        return;

    i = -1;
    while (++i < rules->philo_num)
        pthread_join(philo[i].thread, NULL);
}


void close_program(t_rules *rules, t_philo *philo)
{
    join_threads(rules, philo);
    mutex_destroyer(rules);
    free_all(rules, philo);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:04:46 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/29 20:59:11 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int set_mutex(t_rules *rules)
{
    int i;

    i = -1;
    rules->forks = malloc(rules->philo_num * sizeof(pthread_mutex_t));
    if (!rules->forks)
        return (1);
    while (++i < rules->philo_num)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&rules->forks[i]);
            free(rules->forks);
            return (1);
        }
    }
    if (pthread_mutex_init(&rules->check, NULL) != 0
        || pthread_mutex_init(&rules->eat, NULL) != 0
        || pthread_mutex_init(&rules->monitor, NULL) != 0
        || pthread_mutex_init(&rules->end, NULL) != 0
        || pthread_mutex_init(&rules->routine, NULL) != 0
        || pthread_mutex_init(&rules->write, NULL) != 0)
    {
        mutex_destroyer(rules);
        return (1);
    }
    return (0);
}

int init_data(t_rules *rules, char **argv)
{
    rules->philo_num = atoi(argv[1]);
    rules->time_die = atoi(argv[2]);
    rules->time_eat = atoi(argv[3]);
    rules->time_sleep = atoi(argv[4]);
    if (argv[5])
        rules->meals_num = atoi(argv[5]);
    else
        rules->meals_num = -1;
    rules->status = STILL;
    rules->philos_full = 0;
    rules->start_time = get_time();
    pthread_mutex_init(&rules->check, NULL);
    pthread_mutex_init(&rules->end, NULL);
    pthread_mutex_init(&rules->monitor, NULL);
    if (init_forks(rules))
        return (1);
    return (0);
}

int init_forks(t_rules *rules)
{
    int i;

    rules->forks = malloc(rules->philo_num * sizeof(pthread_mutex_t));
    if (!rules->forks)
        return (1);
    i = -1;
    while (++i < rules->philo_num)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
        {
            free(rules->forks);
            return (1);
        }
    }
    return (0);
}

int set_philos(t_rules *rules)
{
    int     i;
    t_philo *philo;

    philo = malloc(sizeof(t_philo) * rules->philo_num);
    if (!philo)
        return (1);
    i = -1;
    while (++i < rules->philo_num)
    {
        philo[i].id = i + 1;
        philo[i].last_meal = get_time();
        philo[i].num_meals = 0;
        philo[i].r_fork = &rules->forks[i];
        if (i + 1 == rules->philo_num)
            philo[i].l_fork = &rules->forks[0];
        else
            philo[i].l_fork = &rules->forks[i + 1];
        philo[i].rules = rules;
        if (pthread_create(&philo[i].thread, NULL, philosopher_routine, (void *)&philo[i]) != 0)
        {
            free(philo);
            return (1);
        }
    }
    monitor(rules, philo);
    return (0);
}

void set_program(t_rules *rules)
{
    if (set_mutex(rules) || set_philos(rules))
    {
        mutex_destroyer(rules);
        return;
    }
}
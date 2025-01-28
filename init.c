/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:04:46 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/28 16:42:32 by cde-paiv         ###   ########.fr       */
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
            return (1);
    }
    if (pthread_mutex_init(&rules->check, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&rules->eat, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&rules->monitor, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&rules->end, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&rules->routine, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&rules->write, NULL) != 0)
        return (1);
    return (0);
}

int set_philos(t_rules *rules)
{
    int     i;
    t_philo *philos;

    philos = malloc(sizeof(t_philo) * rules->philo_num);
    if (!philos)
        return (1);
    i = -1;
    while (++i < rules->philo_num)
    {
        philos[i].id = i + 1;
        philos[i].last_meal = get_time();
        philos[i].num_meals = 0;
        philos[i].r_fork = &rules->forks[i];
        if (i + 1 == rules->philo_num)
            philos[i].l_fork = &rules->forks[0];
        else
            philos[i].l_fork = &rules->forks[i + 1];
        philos[i].rules = rules;
        if (pthread_create(&philos[i].thread, NULL, routine, (void *)&philos[i]) != 0)
            return (1);
    }
    monitor(rules, philos);
    return (0);
}

void    set_program(t_rules *rules)
{
    if (set_mutex(rules))
        return ;
    if (set_philos(rules))
        return ;
}
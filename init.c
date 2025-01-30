/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:04:46 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/30 22:09:26 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t *alloc_forks(int philo_num)
{
    pthread_mutex_t *ret;

    ret = malloc(philo_num * sizeof(pthread_mutex_t));
    if (!ret)
        return (NULL);
    return (ret);
}

static void    init_forks(t_philo *philo, pthread_mutex_t **forks, int i, int total)
{
   if (i + 1 == total)
   {
        philo->l_fork = &(*forks)[(i + 1) % total];
        philo->r_fork = &(*forks)[i];
   }
   else
   {
    philo->l_fork = &(*forks)[i];
    philo->r_fork = &(*forks)[(i + 1) % total];
   }
}

static int  init_philos(t_rules *rules)
{
    int     i;
    t_philo *temp_phi;
    pthread_mutex_t *philo_forks;

    i = -1;
    temp_phi = malloc(sizeof(t_philo) * rules->philo_num);
    philo_forks = alloc_forks(rules->philo_num);
    while (++i < rules->philo_num)
        pthread_mutex_init(&philo_forks[i], NULL);
    rules->forks = philo_forks;
    i = -1;
    while (++i < rules->philo_num)
    {
        init_forks(&temp_phi[i], &philo_forks, i, rules->philo_num);
        temp_phi[i].id = i;
        temp_phi[i].last_meal = rules->start_time;
        temp_phi[i].is_full = 0;
        temp_phi[i].rules = rules;
    }
    rules->philos = temp_phi;
    return (0);
}

static int  set_program(int argc, char **argv, t_rules *rules)
{
    rules->philo_num = ft_atoi(argv[1]);
    rules->time_die = ft_atoi(argv[2]);
    rules->time_eat = ft_atoi(argv[3]);
    rules->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        rules->meals_num = atoi(argv[5]);
    if (rules->time_die == -1 || rules->time_eat == -1 ||
        rules->time_die == -1 || rules->meals_num == -1 ||
        rules->philo_num == -1)
        return (-3);
    return (0);
}

int init_data(int argc, char **argv, t_rules *rules)
{
    int arg_error;

    if (argc < 5 || argc > 6)
        return (-1);
    arg_error = check_args(argc, argv);
    if (arg_error < 0)
        return (arg_error);
    arg_error = set_program(argc, argv, rules);
	if (arg_error < 0)
    pthread_mutex_init(&rules->print_mutex, NULL);
    pthread_mutex_init(&rules->stop_mutex, NULL);
    pthread_mutex_init(&rules->full_mutex, NULL);
    pthread_mutex_init(&rules->last_meal_mutex, NULL);
    rules->start_time = get_current_time();
    init_philos(rules);
    return (0);
}
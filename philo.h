/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:01:15 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/28 18:14:39 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define STILL 0
# define OVER 1

typedef struct s_rules
{
    int philo_num;
    int time_die;
    int time_eat;
    int time_sleep;
    int meals_num;
    int status;
    int philos_full;
    long    start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t write;
    pthread_mutex_t check;
    pthread_mutex_t eat;
    pthread_mutex_t end;
    pthread_mutex_t monitor;
    pthread_mutex_t routine;
} t_rules;

typedef struct s_philo
{
    int id;
    pthread_t   thread;
    int num_meals;
    long    last_meal;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    t_rules *rules;
} t_philo;

/* Utils */
long        get_time(void);
void        messages(t_philo *philo, char *text);
void        ft_sleep(long time);
int         ft_atoi(const char *str);

/* Init */
void        set_program(t_rules *rules);
int         set_mutex(t_rules *rules);
int         set_philos(t_rules *rules);

/* Monitor */
void        monitor(t_rules *rules, t_philo *philos);
int         check_life(t_philo *philo);
int         check_break(t_philo *philo);

#endif
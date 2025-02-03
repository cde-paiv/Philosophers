/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:01:15 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/03 20:54:15 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

# define THINK 5
# define SLEEP 6
# define FORK 7
# define EAT 8
# define DIE 9

typedef struct s_philo	t_philo;

typedef struct s_rules
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meals_num;
	int				has_anyone_died;
	long int		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	last_meal_mutex;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				is_full;
	long int		last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_rules			*rules;
}	t_philo;

/* Main*/
int		main(int argc, char **argv);
void	free_all(t_rules *rules);
int		launch_threads(t_rules *rules);

/* Utils */
long	int	philo_print(t_philo *philo, int action);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);

/* Init */
int		init_data(int argc, char **argv, t_rules *rules);

/* error */
int		check_args(int argc, char **argv);
void	display_error_msg(int error);

/* threads */
int		has_died(t_philo *philo);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		thinking(t_philo *philo);
void	*routine(void *ptr);

/* time */
long	int	get_current_time(void);
void	my_sleep(int sleep, long int last_meal);
void	*check_time(void *ptr);

#endif

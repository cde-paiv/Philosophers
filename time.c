/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:29:37 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/03 19:29:03 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	kill_philo(t_rules *rules, long int lm_time, int i)
{
	if (lm_time >= rules->time_die)
	{
		pthread_mutex_lock(&rules->stop_mutex);
		rules->has_anyone_died = 1;
		pthread_mutex_unlock(&rules->stop_mutex);
		philo_print(&rules->philos[i], DIE);
		return (1);
	}
	return (0);
}

long int	get_current_time(void)
{
	struct timeval	start_time;
	long int		ret;

	gettimeofday(&start_time, NULL);
	ret = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
	return (ret);
}

void	my_sleep(int sleep, long int last_meal)
{
	long int	start;

	start = get_current_time();
	while (start - last_meal < sleep)
	{
		start = get_current_time();
		usleep(100);
	}
}

void	*check_time(void *ptr)
{
	t_rules		*rules;
	long int	lm_time;
	int			i;

	rules = (t_rules *)ptr;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&rules->last_meal_mutex);
		lm_time = get_current_time() - rules->philos[i].last_meal;
		pthread_mutex_unlock(&rules->last_meal_mutex);
		if (kill_philo(rules, lm_time, i))
			return (NULL);
		pthread_mutex_lock(&rules->full_mutex);
		if (rules->philos[i].is_full)
		{
			pthread_mutex_unlock(&rules->full_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&rules->full_mutex);
		if (++i == rules->philo_num)
			i = 0;
		usleep(2000);
	}
	return (NULL);
}

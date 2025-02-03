/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:29:37 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/03 19:39:00 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_died(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->rules->stop_mutex);
	if (philo->rules->has_anyone_died == 1)
		ret = 1;
	pthread_mutex_unlock(&philo->rules->stop_mutex);
	return (ret);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	if (has_died(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (-1);
	}
	philo_print(philo, FORK);
	pthread_mutex_lock(&philo->rules->last_meal_mutex);
	philo->last_meal = philo_print(philo, EAT);
	pthread_mutex_unlock(&philo->rules->last_meal_mutex);
	my_sleep(philo->rules->time_eat, philo->last_meal);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	long int	time;

	if (has_died(philo))
		return (-1);
	time = philo_print(philo, SLEEP);
	my_sleep(philo->rules->time_sleep, time);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (has_died(philo))
		return (-1);
	philo_print(philo, THINK);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	int		count;

	philo = (t_philo *)ptr;
	count = -1;
	while (!has_died(philo) \
		&& (++count < philo->rules->meals_num || philo->rules->meals_num == 0))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	pthread_mutex_lock(&philo->rules->full_mutex);
	philo->is_full = 1;
	pthread_mutex_unlock(&philo->rules->full_mutex);
	return (NULL);
}

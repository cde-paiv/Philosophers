/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:30:14 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/30 21:52:34 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_rules *rules)
{
	int	i;

	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->stop_mutex);
	pthread_mutex_destroy(&rules->full_mutex);
	pthread_mutex_destroy(&rules->last_meal_mutex);
	i = -1;
	while (++i < rules->philo_num)
		pthread_mutex_destroy(&rules->forks[i]);
	free(rules->forks);
	free(rules->philos);
}

int	launch_threads(t_rules *rules)
{
	pthread_t	*th;
	int			j;

	th = malloc((rules->philo_num + 1) * sizeof(pthread_t));
    j = -1;
	while (++j < rules->philo_num)
	{
		if (pthread_create(&th[j], NULL, &routine, &rules->philos[j]))
			return (1);
	}
	if (pthread_create(&th[j], NULL, &check_time, rules))
		return (1);
	j = -1;
	while (++j < rules->philo_num + 1)
	{
		if (pthread_join(th[j], NULL))
			return (2);
	}
	free(th);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		error;

	ft_bzero(&rules, sizeof(t_rules));
	error = init_data(argc, argv, &rules);
	if (error != 0)
	{
		display_error_msg(error);
		return (1);
	}
	if (launch_threads(&rules))
		return (1);
	free_all(&rules);
	return (0);
}
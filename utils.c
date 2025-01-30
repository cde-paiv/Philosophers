/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:20:32 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/30 21:54:43 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;
	int	i;

	num = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + nptr[i] - '0';
		i++;
	}
	return (num * sign);
}

void	ft_bzero(void *s, size_t n)
{
	char	*s_cpy;

	s_cpy = s;
	while (n--)
		*s_cpy++ = 0;
}

long int    philo_print(t_philo *philo, int action)
{
    long int    time;

    pthread_mutex_lock(&philo->rules->print_mutex);
    time = get_current_time();
    if (action == FORK)
        printf("%ld %d has taken a fork.\n %ld %d has taken a fork.\n",
            time - philo->rules->start_time, philo->id + 1,
            time - philo->rules->start_time, philo->id + 1);
    else if (action == EAT)
        printf("%ld %d is eating.\n", time - philo->rules->start_time, philo->id + 1);
    else if (action == SLEEP)
		printf("%ld %d is sleeping.\n", time - philo->rules->start_time, philo->id + 1);
	else if (action == THINK)
		printf("%ld %d is thinking.\n", time - philo->rules->start_time, philo->id + 1);
	else if (action == DIE)
		printf("%ld %d died.\n", time - philo->rules->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->rules->print_mutex);
	return (time);
}

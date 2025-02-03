/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:48:47 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/03 19:18:16 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	x;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '\0')
			return (-5);
		x = 0;
		if (argv[i][0] == '-' || argv[i][0] == '+')
		{
			if (argv[i][0] == '-')
				return (-2);
			x++;
		}
		while (argv[i][x])
		{
			if (argv[i][x] < '0' || argv[i][x] > '9')
				return (-3);
			x++;
		}
	}
	return (0);
}

void	display_error_msg(int error)
{
	if (error == -1)
		printf("\nError: Wrong number of arguments.\n");
	else if (error == -2)
		printf("\nError: Neither time(s) nor people can be negative. \
C'mon man...\n");
	else if (error == -3)
		printf("\nError: Arguments must be integers greater than zero. \
Remember to respect the boundries.\n");
	else if (error == -5)
		printf("\nError: Empty string? Realy???\n");
	printf("Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n\n");
}

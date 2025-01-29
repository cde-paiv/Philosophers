/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:30:14 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/29 21:01:09 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_rules rules;
    t_philo *philo;

    if (argc != 5 && argc != 6)
    {
        printf("Wrong number of arguments\n");
        printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]\n");
        return (1);
    }
    if (init_data(&rules, argv))
    {
        printf("Error in initialization\n");
        return (1);
    }
    philo = malloc(sizeof(t_philo) * rules.philo_num);
    if (!philo)
    {
        printf("Error: Memory allocation failed\n");
        mutex_destroyer(&rules);
        free(rules.forks);
        return (1);
    }
    if (set_philos(&rules))
    {
        printf("Error: Failed to initialize philosophers\n");
        free(philo);
        mutex_destroyer(&rules);
        free(rules.forks);
        return (1);
    }
    monitor(&rules, philo);
    close_program(&rules, philo);
    return (0);
}
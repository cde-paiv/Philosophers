/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:48:47 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/29 20:45:36 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void monitor(t_rules *rules, t_philo *philos)
{
    int i;
    int finish;

    finish = STILL;
    while (finish == STILL)
    {
        i = -1;
        while (++i < rules->philo_num)
        {
            pthread_mutex_lock(&rules->monitor);
            if (rules->status == OVER)
            {
                pthread_mutex_unlock(&rules->monitor);
                finish = OVER;
                break;
            }
            pthread_mutex_unlock(&rules->monitor);
            if (check_life(&philos[i]) == OVER)
            {
                pthread_mutex_lock(&rules->monitor);
                rules->status = OVER;
                pthread_mutex_unlock(&rules->monitor);
                finish = OVER;
                break;
            }
        }
        usleep(500);
    }
    close_program(rules, philos);
}
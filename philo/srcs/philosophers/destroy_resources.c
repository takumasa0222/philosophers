/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:25:26 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/02 20:47:27 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void	release_resources(t_philosopher *philos)
{
	int		i;
	long	num_of_philo;

	num_of_philo = philos->shared->num_of_philos;
	i = -1;
	while (++i < num_of_philo)
		pthread_mutex_destroy(&philos->forks[i]);
	free(philos->forks);
    pthread_mutex_destroy(&philos->shared->meal_mutex);
    pthread_mutex_destroy(&philos->shared->stop_mutex);
}

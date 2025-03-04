/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:18:52 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/05 03:00:23 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include "../../includes/utils.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

int	dining(t_philosopher *philo)
{
	take_forks(philo);
	record_dining(philo->shared, philo->id);
	print_philo_action(philo->id, EATING);
	usleep(philo->shared->time_to_eat * 1000);
	release_forks(philo);
	return (EXIT_SUCCESS);
}

int	take_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % (philo->shared->num_of_philos);
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&philo->forks[left_fork]);
		print_philo_action(philo->id, TAKE_A_FORK);
		pthread_mutex_lock(&philo->forks[right_fork]);
		print_philo_action(philo->id, TAKE_A_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[right_fork]);
		print_philo_action(philo->id, TAKE_A_FORK);
		pthread_mutex_lock(&philo->forks[left_fork]);
		print_philo_action(philo->id, TAKE_A_FORK);
	}
	return (EXIT_SUCCESS);
}

void	record_dining(t_philo_ctx *shared, int p_id)
{
	pthread_mutex_lock(&shared->meal_mutex);
	shared->last_meal_time[p_id - 1] = retrive_current_ms();
	shared->meal_cnt[p_id - 1] = shared->meal_cnt[p_id - 1] + 1;
	pthread_mutex_unlock(&shared->meal_mutex);
}

void	release_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % (philo->shared->num_of_philos);
	if (left_fork < right_fork)
	{
		pthread_mutex_unlock(&philo->forks[right_fork]);
		pthread_mutex_unlock(&philo->forks[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[left_fork]);
		pthread_mutex_unlock(&philo->forks[right_fork]);
	}
}

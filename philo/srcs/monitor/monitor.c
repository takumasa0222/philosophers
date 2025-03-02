/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:09:34 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/02 22:59:50 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include "../../includes/monitor.h"
#include "../../includes/utils.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void	*start_monitor_thread(void *arg)
{
	t_philo_ctx	*shared;
	long		now;

	shared = (t_philo_ctx *)arg;
	while (!is_stopped(shared))
	{
		usleep(1000);
		now = retrive_current_ms();
		check_starvation(shared, now);
	}
	return (NULL);
}

void	check_starvation(t_philo_ctx *shared, long now)
{
	int	i;
	int	full_state_philo;

	full_state_philo = 0;
	pthread_mutex_lock(&shared->meal_mutex);
	i = -1;
	while (++i < shared->num_of_philos)
	{
		if (now - shared->last_meal_time[i] > shared->time_to_die)
		{
			print_philo_action(i + 1, DEAD);
			pthread_mutex_unlock(&shared->meal_mutex);
			set_stop(shared);
			return ;
		}
		if (shared->num_of_must_eat != MUST_EAT_NOT_SET \
		&& shared->num_of_must_eat <= shared->meal_cnt[i])
			full_state_philo++;
	}
	if (full_state_philo == shared->num_of_philos)
		set_stop(shared);
	pthread_mutex_unlock(&shared->meal_mutex);
}

void	set_stop(t_philo_ctx *shared)
{
	pthread_mutex_lock(&shared->stop_mutex);
	shared->stop = 1;
	pthread_mutex_unlock(&shared->stop_mutex);
}

int	is_stopped(t_philo_ctx *shared)
{
	int	ret;

	pthread_mutex_lock(&shared->stop_mutex);
	ret = shared->stop;
	pthread_mutex_unlock(&shared->stop_mutex);
	return (ret);
}

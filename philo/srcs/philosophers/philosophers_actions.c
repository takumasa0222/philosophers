/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:06:58 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/21 22:46:53 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include "../../includes/utils.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void	sleeping(t_philosopher *philo)
{
	print_wrapper(philo->shared, philo->id, SLEEP);
	usleep(1000 * philo->shared->time_to_sleep);
}

void	thinking(t_philosopher *philo)
{
	print_wrapper(philo->shared, philo->id, THINK);
	usleep(5000);
}

void	print_wrapper(t_philo_ctx *shared, int philo_id, t_philo_msg msg)
{
	pthread_mutex_lock(&shared->write_mutex);
	print_philo_action(philo_id, msg);
	pthread_mutex_unlock(&shared->write_mutex);
}

void	print_philo_action(int philo_id, t_philo_msg msg)
{
	long	now;

	now = retrive_current_ms();
	if (msg == SLEEP)
		printf("%ld %d is sleeping\n", now, philo_id);
	else if (msg == THINK)
		printf("%ld %d is thinking\n", now, philo_id);
	else if (msg == TAKE_A_FORK)
		printf("%ld %d has taken a fork\n", now, philo_id);
	else if (msg == EATING)
		printf("%ld %d is eating\n", now, philo_id);
	else if (msg == DEAD)
		printf("%ld %d died\n", now, philo_id);
}

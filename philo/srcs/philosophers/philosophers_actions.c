/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:06:58 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/02 23:01:27 by tamatsuu         ###   ########.fr       */
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
	print_philo_action(philo->id, SLEEP);
	usleep(1000 * philo->shared->time_to_sleep);
}

void	thinking(t_philosopher *philo)
{
	print_philo_action(philo->id, THINK);
}

void	print_philo_action(int philo_id, t_philo_msg msg)
{
	long	now;

	now = retrive_current_ms();
	if (msg == SLEEP)
		printf("%ld %d is sleeping", now, philo_id);
	else if (msg == THINK)
		printf("%ld %d is thinking", now, philo_id);
	else if (msg == TAKE_A_FORK)
		printf("%ld %d  has taken a fork", now, philo_id);
	else if (msg == EATING)
		printf("%ld %d is eating", now, philo_id);
	else if (msg == DEAD)
		printf("%ld %d died", now, philo_id);
}

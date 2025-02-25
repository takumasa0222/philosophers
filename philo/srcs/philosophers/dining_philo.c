/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:18:52 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/25 17:24:14 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

int	dining(t_philosopher *philo)
{
	take_forks(philo);
	record_last_time_dining(philo->shared);
	print_philo_action(EATING);
	usleep(philo->shared->time_to_eat);
	release_forks(philo);
	return (EXIT_SUCCESS);
}

int	take_forks(t_philosopher *philo)
{
	int				lock_ret;
	unsigned int	usecs;

	usecs = TRY_GET_FORK_INT_USEC;
	while (1)
	{
		lock_ret = ptread_mutex_lock(philo->fork_arry[ctx->philo_index]);
		if (!lock_ret)
			break ;
		else
		{
			usleep(usecs);
			if (check_philo_stavation(last_dining_time))
				return (EXIT_FAILURE);
		}
	}
	print_philo_action(TAKE_A_FOLK);
	return (EXIT_SUCCESS);
}

release_forks(t_philo_ctx *ctx)
{
	pthread_mutex_unlock(ctx->fork_arry[ctx->philo_index]);
	pthread_mutex_unlock(ctx->fork_arry[ctx->philo_index]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:18:52 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/19 20:09:19 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

int	dining(t_philo_ctx *ctx, suseconds_t last_dining_time)
{
	if (take_left_fork(ctx, last_dining_time))
		return (EXIT_FAILURE);
	if (take_right_fork(ctx, last_dining_time))
		return (EXIT_FAILURE);
	print_philo_action(EATING);
	usleep(ctx->time_to_eat);
	return (EXIT_SUCCESS);
}

int	take_left_fork(t_philo_ctx *ctx, suseconds_t last_dining_time)
{
	int				lock_ret;
	unsigned int	usecs;

	usecs = TRY_GET_FORK_INT_USEC;
	while (1)
	{
		lock_ret = ptread_mutex_lock(ctx->fork_arry[ctx->philo_index]);
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

int	take_right_fork(t_philo_ctx *ctx, suseconds_t last_dining_time)
{
	int				lock_ret;
	unsigned int	usecs;

	usecs = TRY_GET_FORK_INT_USEC;
	while (1)
	{
		lock_ret = ptread_mutex_lock(ctx->fork_arry[ctx->philo_index]);
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

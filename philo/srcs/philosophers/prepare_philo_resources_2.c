/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_philo_resources_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:00:40 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/20 18:54:28 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"
#include "../../includes/utils.h"
#include <stdlib.h>

bool	validate_ctx_set_value(t_philo_ctx *ctx)
{
	if (ctx->num_of_philos <= 0)
		return (write_error(ERR_NUM_OF_PHILP), false);
	if (ctx->time_to_die < 0 && ctx->time_to_die <= MAX_MS_LIMIT)
		return (write_error(ERR_TIME_TO_DIE), false);
	if (ctx->time_to_eat < 0 && ctx->time_to_eat <= MAX_MS_LIMIT)
		return (write_error(ERR_TIME_TO_EAT), false);
	if (ctx->time_to_sleep < 0 && ctx->time_to_sleep <= MAX_MS_LIMIT)
		return (write_error(ERR_TIME_TO_SLEEP), false);
	if (ctx->num_of_must_eat != MUST_EAT_NOT_SET && ctx->num_of_must_eat < 0)
		return (write_error(ERR_MUST_EAT_NUM), false);
	return (true);
}

int	init_ctx(t_philo_ctx **ctx, char **argv)
{
	if (!ctx)
		return (0);
	*ctx = malloc(sizeof (t_philo_ctx) * 1);
	if (!*ctx)
	{
		write_error(ERR_MALLOC);
		return (0);
	}
	(*ctx)->num_of_philos = ft_strtol(argv[1]);
	(*ctx)->time_to_die = ft_strtol(argv[2]);
	(*ctx)->time_to_eat = ft_strtol(argv[3]);
	(*ctx)->time_to_sleep = ft_strtol(argv[4]);
	(*ctx)->stop = 0;
	if (argv[5])
		(*ctx)->num_of_must_eat = ft_strtol(argv[5]);
	else
		(*ctx)->num_of_must_eat = MUST_EAT_NOT_SET;
	if (!validate_ctx_set_value(*ctx) || !init_mutex_members(ctx))
	{
		free_ctx(0, ctx);
		return (0);
	}
	return (1);
}

int	init_mutex_members(t_philo_ctx **ctx)
{
	int				i;
	long			now;
	long			num_of_philos;

	if (!ctx || !*ctx)
		return (0);
	num_of_philos = (*ctx)->num_of_philos;
	(*ctx)->last_meal_time = malloc(num_of_philos * sizeof(long));
	(*ctx)->meal_cnt = malloc(num_of_philos * sizeof(long));
	if (!(*ctx)->last_meal_time || !(*ctx)->meal_cnt)
		return (0);
	pthread_mutex_init(&(*ctx)->meal_mutex, NULL);
	pthread_mutex_init(&(*ctx)->stop_mutex, NULL);
	pthread_mutex_init(&(*ctx)->write_mutex, NULL);
	now = retrive_current_ms();
	pthread_mutex_lock(&(*ctx)->meal_mutex);
	i = -1;
	while (++i < num_of_philos)
	{
		(*ctx)->last_meal_time[i] = now;
		(*ctx)->meal_cnt[i] = 0;
	}
	pthread_mutex_unlock(&(*ctx)->meal_mutex);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_philo_resources.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:49:44 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/12 20:56:41 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include "../../includes/utils.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

int	init_ctx(t_philo_ctx **ctx, char **argv)
{
	if (!ctx)
		return (0);
	*ctx = malloc(sizeof (t_philo_ctx) * 1);
	if (!*ctx)
		return (0);
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
		//free_ctx(ctx);
		//write_error();
		return (0);
	}
	return (1);
}

int	init_forks(long num_of_philos, pthread_mutex_t **forks)
{
	long	i;

	*forks = malloc(num_of_philos * sizeof(pthread_mutex_t));
	if (!*forks)
		return (0);
	i = -1;
	while (++i < num_of_philos)
		pthread_mutex_init(&(*forks)[i], NULL);
	return (1);
}

int	init_approve(long num_phl, pthread_mutex_t **approve, int **approval)
{
	long	i;

	*approve = malloc(num_phl * sizeof(pthread_mutex_t));
	if (!*approve)
		return (0);
	*approval = malloc(num_phl * sizeof(int));
	if (!*approval)
		return (0);
	i = -1;
	while (++i < num_phl)
		pthread_mutex_init(&(*approve)[i], NULL);
	while (++i < num_phl)
		*approval[i] = APPROVED;
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

int	init_philos(t_philo_ctx **ctx, t_philosopher ***philos)
{
	long			num_of_philos;
	long			i;
	pthread_mutex_t	*forks;
	//pthread_mutex_t	*approve;
	//int				*approval;

	if (!ctx || !*ctx)
		return (0);
	num_of_philos = (*ctx)->num_of_philos;
	*philos = malloc(num_of_philos * sizeof(t_philosopher *));
	if (!*philos)
		return (0);
	// need to free philos
	if (!init_forks(num_of_philos, &forks))
		return (0);
	//if (!init_approve(num_of_philos, &approve, &approval))
	//	return (0);
	i = -1;
	while (++i < num_of_philos)
	{
		(*philos)[i] = malloc(sizeof(t_philosopher));
		(*philos)[i]->id = i + 1;
		(*philos)[i]->shared = (*ctx);
		(*philos)[i]->forks = forks;
		//(*philos)[i]->approve = approve;
		//(*philos)[i]->approval = approval;
	}
	return (1);
}

bool	validate_ctx_set_value(t_philo_ctx *ctx)
{
	if (ctx->num_of_philos <= 0)
		return (false);
	if (ctx->time_to_die < 0 && ctx->time_to_die <= MAX_MS_LIMIT)
		return (false);
	if (ctx->time_to_eat < 0 && ctx->time_to_eat <= MAX_MS_LIMIT)
		return (false);
	if (ctx->time_to_sleep < 0 && ctx->time_to_sleep <= MAX_MS_LIMIT)
		return (false);
	if (ctx->num_of_must_eat != MUST_EAT_NOT_SET && ctx->num_of_must_eat < 0)
		return (false);
	return (true);
}

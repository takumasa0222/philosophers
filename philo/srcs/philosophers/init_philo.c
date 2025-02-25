/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:08:37 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/25 17:09:28 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

// pthread_detach
// pthread_join
// pthread_mutex_init
// pthread_mutex_destroy 
// pthread_mutex_lock
// pthread_mutex_unlock
// pthread_create

int	start_philo(char **argv)
{
	t_philo_ctx		*ctx;
	pthread_mutex_t	*forks;

	if (!init_ctx(&ctx, argv))
		return (EXIT_FAILURE);
	forks = malloc(ctx->num_of_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (EXIT_FAILURE);
	while 
	start_life_of_philos(ctx);
	return (EXIT_SUCCESS);
}

int	init_ctx(t_philo_ctx **ctx, char **argv)
{
	if (!ctx)
		return (EXIT_FAILURE);
	*ctx = malloc(sizeof (t_philo_ctx) * 1);
	if (!*ctx)
		return (EXIT_FAILURE);
	(*ctx)->num_of_philos = ft_strtol(argv[1]);
	(*ctx)->time_to_die = ft_strtol(argv[2]);
	(*ctx)->time_to_eat = ft_strtol(argv[3]);
	(*ctx)->time_to_sleep = ft_strtol(argv[4]);
	if (argv[5])
		(*ctx)->num_of_must_eat = ft_strtol(argv[5]);
	else
		(*ctx)->num_of_must_eat = DEFAULT_VAL;
	if (!validate_set_value(*ctx))
	{
		free_ctx(ctx);
		write_error();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	start_life_of_philos(t_philo_ctx *ctx)
{
	long					i;
	static pthread_mutex_t	*fork_arry[200] = {0};
	pthread_t				*thread_ids[200] = {0};
	t_philo_ctx				*cpy_ctx;

	if (!create_forks(fork_arry, ctx))
		return (EXIT_FAILURE);
	if (!init_thread_ids(thread_ids, ctx))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < ctx->num_of_philos)
		pthread_mutex_init(fork_arry[i], NULL);
	i = -1;
	while (++i < ctx->num_of_philos)
	{
		cpy_ctx = NULL;
		cpy_ctx = dup_ctx(ctx);
		cpy_ctx->philo_index = i;
		pthread_create(thread_ids[i], NULL, start_life_of_philo, &cpy_ctx);
	}
}

int	start_life_of_philo(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		dining(philo);
		if (check_philo_starvation(philo->shared))
			break;
		sleeping();
		thinking();
		print_philo_action(SLEEP);
		usleep(ctx->time_to_sleep);
		print_philo_action(THINK);
	}
}

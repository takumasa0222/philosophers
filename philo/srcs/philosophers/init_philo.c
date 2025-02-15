/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:08:37 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/15 23:34:31 by tamatsuu         ###   ########.fr       */
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
	t_philo_ctx	*ctx;

	if (!init_ctx(&ctx, argv))
		return (EXIT_FAILURE);
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
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	start_life_of_philos(t_philo_ctx *ctx)
{
	long			i;
	pthread_mutex_t	**fork_arry;
	pthread_t		**thread_ids;
	t_philo_ctx		*cpy_ctx;

	if (!create_forks(&fork_arry, ctx))
		return (EXIT_FAILURE);
	if (!init_thread_ids(&thread_ids, ctx))
	{
		clean_up_resources(&fork_arry, NULL);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < ctx->num_of_philos)
		pthread_mutex_init(fork_arry[i], NULL);
	i = -1;
	while (++i < ctx->num_of_philos)
	{
		cpy_ctx = dup_ctx(ctx);
		cpy_ctx->philo_index = i;
		pthread_create(thread_ids[i], NULL, start_life_of_philo, cpy_ctx);
	}
}

int	start_life_of_philo(void *arg)
{
	int				meal_cnt;
	t_philo_ctx		*ctx;
	suseconds_t		last_dining_time;
	struct timeval	*time;

	ctx = (t_philo_ctx *)arg;
	gettimeofday(time, NULL);
	last_dining_time = retrive_current_time();
	while (1)
	{
		take_left_fork(ctx);
		ptread_mutex_lock(ctx->fork_arry[ctx->philo_index]);
		print_philo_action(TAKE_A_FOLK);
		if (check_philo_stavation(last_dining_time))
			return (kill_philo(ctx));
		try_take_right_fork(ctx);
		ptread_mutex_lock(ctx->fork_arry[ctx->philo_index]);
		print_philo_action(TAKE_A_FOLK);
		if (check_philo_stavation(last_dining_time))
			return (kill_philo(ctx));
		print_philo_action(EATING);
		usleep(ctx->time_to_eat);
		last_dining_time = retrive_current_time();
		release_right_fork(ctx);
		release_left_fork(ctx);
		pthread_mutex_unlock(ctx->fork_arry[ctx->philo_index]);
		pthread_mutex_unlock(ctx->fork_arry[ctx->philo_index]);
		print_philo_action(SLEEP);
		usleep(ctx->time_to_sleep);
		if (check_philo_stavation(last_dining_time))
			return (kill_philo(ctx));
		print_philo_action(THINK);
	}
}

create_philo();
create_folks();
sleep_philo();
take_left_folk();
take_right_folk();
kill_philo();
retrive_current_time();
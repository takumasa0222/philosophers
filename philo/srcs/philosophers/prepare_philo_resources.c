/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_philo_resources.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:49:44 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/20 18:52:53 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include "../../includes/utils.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

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

int	init_philos(t_philo_ctx **ctx, t_philosopher ***phls, pthread_mutex_t **f)
{
	long			num_of_philos;

	if (!ctx || !*ctx)
		return (0);
	num_of_philos = (*ctx)->num_of_philos;
	*phls = malloc(num_of_philos * sizeof(t_philosopher *));
	if (!*phls)
		return (free_ctx(1, ctx), 0);
	if (!init_forks(num_of_philos, f))
		return (free_forks(num_of_philos, f), \
		free_ctx(1, ctx), free(*phls), 0);
	if (!set_phil_val(ctx, phls, f))
		return (free_ctx(1, ctx), free_forks(num_of_philos, f), 0);
	return (1);
}

int	set_phil_val(t_philo_ctx **c, t_philosopher ***p, pthread_mutex_t **f)
{
	long			i;
	long			num_of_philos;

	i = 0;
	num_of_philos = (*c)->num_of_philos;
	while (i < num_of_philos)
	{
		(*p)[i] = malloc(sizeof(t_philosopher));
		if (!(*p)[i])
		{
			if (i)
				free_philo(p, i);
			write_error(ERR_MALLOC);
			return (0);
		}
		(*p)[i]->id = i + 1;
		(*p)[i]->shared = *c;
		(*p)[i]->forks = *f;
		i++;
	}
	return (1);
}

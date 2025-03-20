/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:01:29 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/20 18:05:16 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include "../../includes/utils.h"
#include <pthread.h>

void	free_ctx(int is_mutex_include, t_philo_ctx **ctx)
{
	if (!ctx || !*ctx)
	{
		write_error(NULL);
		return ;
	}
	if (is_mutex_include)
	{
		pthread_mutex_destroy(&(*ctx)->meal_mutex);
		pthread_mutex_destroy(&(*ctx)->stop_mutex);
		pthread_mutex_destroy(&(*ctx)->write_mutex);
	}
	if ((*ctx)->meal_cnt)
		free((*ctx)->meal_cnt);
	if ((*ctx)->last_meal_time)
		free((*ctx)->last_meal_time);
	free(*ctx);
}

void	free_philo(t_philosopher ***philos, long end)
{
	long	i;

	if (!philos || !*philos)
		return ;
	i = 0;
	while (i < end)
	{
		if ((*philos)[i])
			free ((*philos)[i]);
		i++;
	}
	free(*philos);
	*philos = NULL;
}

void	free_forks(long num, pthread_mutex_t **forks)
{
	long	i;

	i = 0;
	while (+i < num)
	{
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	free(*forks);
	*forks = NULL;
}

void	free_res(t_philosopher ***p, pthread_mutex_t **f, t_philo_ctx **ctx)
{
	long	num_of_philos;

	num_of_philos = (*ctx)->num_of_philos;
	free_philo(p, num_of_philos);
	free_forks(num_of_philos, f);
	free_ctx(1, ctx);
}

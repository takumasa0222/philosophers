/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:08:37 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/20 18:44:39 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "../../includes/monitor.h"
#include "../../includes/utils.h"

int	start_philo(char **argv)
{
	t_philo_ctx		*ctx;
	t_philosopher	**philos;
	pthread_mutex_t	*forks;

	if (!init_ctx(&ctx, argv))
		return (EXIT_FAILURE);
	if (!init_philos(&ctx, &philos, &forks))
		return (EXIT_FAILURE);
	if (ctx->num_of_philos == 1)
		start_single_philo(philos);
	else
		start_life_of_philos(philos);
	free_res(&philos, &forks, &ctx);
	return (EXIT_SUCCESS);
}

int	start_life_of_philos(t_philosopher **ph)
{
	long		num_of_philos;
	int			i;
	pthread_t	t_ids[MAX_NUM_PHILOS];
	pthread_t	monitor_id;

	if (!ph || !*ph)
		return (EXIT_FAILURE);
	num_of_philos = (*ph)->shared->num_of_philos;
	i = -1;
	while (++i < num_of_philos)
		pthread_create(&t_ids[i], NULL, start_philo_thread, ph[i]);
	pthread_create(&monitor_id, NULL, start_monitor_thread, (*ph)->shared);
	i = -1;
	while (++i < num_of_philos)
		pthread_join(t_ids[i], NULL);
	pthread_join(monitor_id, NULL);
	return (EXIT_SUCCESS);
}

void	*start_philo_thread(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		if (is_stopped(philo->shared))
			break ;
		dining(philo);
		if (is_stopped(philo->shared))
			break ;
		sleeping(philo);
		if (is_stopped(philo->shared))
			break ;
		thinking(philo);
	}
	return (NULL);
}

int	start_single_philo(t_philosopher **ph)
{
	pthread_t	t_id;

	pthread_create(&t_id, NULL, start_single_philo_thread, (void *)&(*ph)[0]);
	pthread_join(t_id, NULL);
	return (EXIT_SUCCESS);
}

void	*start_single_philo_thread(void *arg)
{
	t_philosopher	*philo;
	long			now;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(&philo->forks[0]);
	print_philo_action(philo->id, TAKE_A_FORK);
	while (1)
	{
		now = retrive_current_ms();
		usleep(1000);
		if (now - philo->shared->last_meal_time[0] > philo->shared->time_to_die)
			break ;
	}
	print_philo_action(philo->id, DEAD);
	pthread_mutex_unlock(&philo->forks[0]);
	return (EXIT_SUCCESS);
}

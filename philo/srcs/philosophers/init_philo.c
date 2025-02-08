/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:08:37 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/09 03:50:48 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/philosophers.h"
#include <pthread.h>

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

int	start_life_of_philo(t_philo_ctx *ctx)
{
	long			i;
	pthread_mutex_t	**fork_arry;

	if (!create_fork_arry(&fork_arry, ctx))
		return (EXIT_FAILURE);
	i = 0;
	while (i < ctx->num_of_philos)
	{
		pthread_mutex_init(fork_arry[i], NULL);
		i++;
	}
	//i = 0;
	//while (i < ctx->num_of_philos)
	//{
	//	create_philo();
	//}
	
}

create_philo();
create_folks();
sleep_philo();
take_left_folk();
take_right_folk();
kill_philo();


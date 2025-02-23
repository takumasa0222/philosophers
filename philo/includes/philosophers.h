/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:20:33 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/19 20:08:25 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# define DEFAULT_VAL -2
# define TRY_GET_FORK_INT_USEC 10000
# define MS_TO_USEC 1000
# define MAX_MS_LIMIT 100000

typedef struct s_philo_ctx
{
	long				num_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_of_must_eat;
	pthread_mutex_t		**fork_arry;
	long				philo_index;
}	t_philo_ctx;

typedef enum e_philo_msg
{
	TAKE_A_FOLK,
	EATING,
	SLEEP,
	THINK
}	t_philo_msg;

int	start_philo(char **argv);
int	init_ctx(t_philo_ctx **ctx, char **argv);
int	start_life_of_philos(t_philo_ctx *ctx);
int	start_life_of_philo(void *arg);
int	dining(t_philo_ctx *ctx, suseconds_t last_dining_time);
int	take_left_fork(t_philo_ctx *ctx, suseconds_t last_dining_time);
int	take_right_fork(t_philo_ctx *ctx, suseconds_t last_dining_time);
int	release_forks(t_philo_ctx *ctx);
int	check_philo_starvation(t_philo_ctx *ctx, suseconds_t last_dining_usec);

#endif
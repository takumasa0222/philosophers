/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:20:33 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/25 15:53:05 by tamatsuu         ###   ########.fr       */
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
# define MAX_NUM_PHILOS 200

typedef struct s_philo_ctx
{
	pthread_mutex_t		meal_mutex;
	long				last_meal_time[MAX_NUM_PHILOS];
	int					stop;
	pthread_mutex_t		stop_mutex;
	long				num_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_of_must_eat;
}	t_philo_ctx;

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	*forks;
	t_philo_ctx		*shared;
}	t_philosopher;

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
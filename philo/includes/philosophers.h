/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:20:33 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/20 18:03:30 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# define MUST_EAT_NOT_SET -2
# define TRY_GET_FORK_INT_USEC 10000
# define MS_TO_USEC 1000
# define MAX_MS_LIMIT 100000
# define MAX_NUM_PHILOS 1000
# define APPROVED 0
# define PENDING 1

typedef struct s_philo_ctx
{
	pthread_mutex_t		meal_mutex;
	long				*last_meal_time;
	int					stop;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		write_mutex;
	long				num_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_of_must_eat;
	long				*meal_cnt;
}	t_philo_ctx;

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	*forks;
	t_philo_ctx		*shared;
}	t_philosopher;

typedef enum e_philo_msg
{
	TAKE_A_FORK,
	EATING,
	SLEEP,
	THINK,
	DEAD
}	t_philo_msg;

int		start_philo(char **argv);
int		start_life_of_philos(t_philosopher **phls);
void	*start_philo_thread(void *arg);
int		start_single_philo(t_philosopher **phls);
void	*start_single_philo_thread(void *arg);

int		dining(t_philosopher *philo);
int		take_forks(t_philosopher *philo);
void	record_dining(t_philo_ctx *shared, int p_id);
void	release_forks(t_philosopher *philo);

int		init_ctx(t_philo_ctx **ctx, char **argv);
int		init_forks(long num_of_philos, pthread_mutex_t **forks);
int		init_mutex_members(t_philo_ctx **ctx);
int		init_philos(t_philo_ctx **cx, t_philosopher ***p, pthread_mutex_t **f);
int		set_phil_val(t_philo_ctx **c, t_philosopher ***p, pthread_mutex_t **f);
bool	validate_ctx_set_value(t_philo_ctx *ctx);

void	sleeping(t_philosopher *philo);
void	thinking(t_philosopher *philo);
void	print_philo_action(int philo_id, t_philo_msg msg);
#endif
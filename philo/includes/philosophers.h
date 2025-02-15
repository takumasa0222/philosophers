/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:20:33 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/15 22:53:57 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# define DEFAULT_VAL -2

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


#endif
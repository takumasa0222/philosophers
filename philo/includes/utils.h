/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:35:42 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/21 23:01:10 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# define ERR_TOO_FEW_ARGS "Error: Too few arguments provided. \
Expected at least 4"
# define ERR_TOO_MANY_ARGS "Error: Too many arguments provided. \
Maximum allowed is 5"
# define ERR_NULL_ARG "Error: Argument is null."
# define ERR_ARG_TYPE "Error: Argument should be positive numeric."
# define ERR_MALLOC "Error: Malloc failed"
# define ERR_NUM_OF_PHILO "Error: Number of Philosopher is too many"
# define ERR_TIME_TO_EAT "Error: Time to eat should be less than 100,000ms"
# define ERR_TIME_TO_DIE "Error: Time to die should be less than 100,000ms"
# define ERR_TIME_TO_SLEEP "Error: Time to sleep should be less than 100,000ms"
# define ERR_MUST_EAT_NUM "Error: Number of eat should be less than 10,000"

# include <stdbool.h>
# include "./philosophers.h"

bool	validate_arg(int argc, char *argv[]);
bool	check_arg_num(int argc);
bool	check_arg_type(int argc, char **argv);

bool	is_consist_of_number(char *arg);
bool	is_numeric(int c);

long	ft_strtol(const char *str);

long	retrive_current_ms(void);

int		write_error(char *err_msg);

void	free_ctx(int is_mutex_include, t_philo_ctx **ctx);
void	free_philo(t_philosopher ***philos, long end);
void	free_forks(long num, pthread_mutex_t **forks);
void	free_res(t_philosopher ***p, pthread_mutex_t **f, t_philo_ctx **ctx);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:35:42 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/20 18:51:59 by tamatsuu         ###   ########.fr       */
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
# define ERR_NUM_OF_PHILP "Error: Invalid philosopher number"
# define ERR_TIME_TO_EAT "Error: Invalid time to eat"
# define ERR_TIME_TO_DIE "Error: Invalid time to die"
# define ERR_TIME_TO_SLEEP "Error: Invalid time to sleep"
# define ERR_MUST_EAT_NUM "Error: Invalid must eat num"

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
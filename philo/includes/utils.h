/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:35:42 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/02 23:21:18 by tamatsuu         ###   ########.fr       */
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
# include <stdbool.h>


bool	validate_arg(int argc, char *argv[]);
bool	check_arg_num(int argc);
bool	check_arg_type(int argc, char **argv);


bool	is_consist_of_number(char *arg);
bool	is_numeric(int c);

long	ft_strtol(const char *str);

long	retrive_current_ms(void);

int		write_error(char *err_msg);
#endif
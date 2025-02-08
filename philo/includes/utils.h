/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:35:42 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/09 02:47:39 by tamatsuu         ###   ########.fr       */
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

bool	validate_arg(int argc, char *argv[]);
bool	check_arg_num(int argc);
bool	check_arg_type(int argc, char **argv);
bool	is_consist_of_number(char *arg);
bool	is_numeric(int c);

#endif
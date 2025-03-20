/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:29:50 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/20 18:53:32 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "../../includes/philosophers.h"
#include <stdio.h>

bool	validate_arg(int argc, char *argv[])
{
	if (!check_arg_num(argc))
		return (false);
	if (!check_arg_type(argc, argv))
		return (false);
	return (true);
}

bool	check_arg_num(int argc)
{
	if (argc < 5)
	{
		write_error(ERR_TOO_FEW_ARGS);
		return (false);
	}	
	if (6 < argc)
	{
		write_error(ERR_TOO_MANY_ARGS);
		return (false);
	}
	return (true);
}

bool	check_arg_type(int argc, char **argv)
{
	int	i;

	if (!argv && argc < 5)
	{
		write_error(ERR_NULL_ARG);
		return (false);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_consist_of_number(argv[i]))
		{
			write_error(ERR_ARG_TYPE);
			return (false);
		}
		i++;
	}
	return (true);
}

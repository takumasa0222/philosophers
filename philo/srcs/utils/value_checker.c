/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 03:25:23 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/02 23:13:54 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../../includes/utils.h"

bool	is_consist_of_number(char *arg)
{
	size_t	i;

	if (!arg)
		return (false);
	i = 0;
	while (arg[i])
	{
		if (!is_numeric(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_numeric(int c)
{
	return ('0' <= c && c <= '9');
}

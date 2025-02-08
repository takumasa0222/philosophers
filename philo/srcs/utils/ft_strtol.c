/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:49:11 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/09 03:24:10 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/utils.h"
#include <stdio.h>
#include <stdlib.h>

static int	overflowcheck(long res, char c);

long	ft_strtol(const char *str)
{
	long	result;

	result = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' \
	|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	while (is_numeric(*str) && *str)
	{
		if (!overflowcheck(result, *str))
			return (-1);
		result = result * 10 + (long)(*str - 48);
		str++;
	}
	return (result);
}

static int	overflowcheck(long res, char c)
{
	int	i;

	i = c - 48;
	if (LONG_MAX / 10 < res || (LONG_MAX / 10 == res && LONG_MAX % 10 <= i))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

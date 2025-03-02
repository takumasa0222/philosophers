/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:07:24 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/02 23:15:33 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../includes/utils.h"

int	write_error(char *err_msg)
{
	int	i;

	if (!err_msg)
	{
		printf("error\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (err_msg[i])
	{
		write(STDERR_FILENO, &err_msg[i], sizeof(char));
		i++;
	}
	write(STDERR_FILENO, "\n", sizeof(char));
	return (EXIT_SUCCESS);
}

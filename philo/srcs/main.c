/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:21:54 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/09 00:26:51 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (validate_arg(argc, argv))
		start_philo();
	else
	{
		write_error();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

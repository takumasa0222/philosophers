/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:21:54 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/18 02:21:57 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/philosophers.h"

int	main(int argc, char *argv[])
{
	if (validate_arg(argc, argv))
		return (start_philo(argv));
	else
	{
		write_error();
		return (EXIT_FAILURE);
	}
}

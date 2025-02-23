/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:41:38 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/19 20:35:47 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

size_t	retrive_current_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

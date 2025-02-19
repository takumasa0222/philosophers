/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:41:38 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/18 01:54:44 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

suseconds_t	retrive_current_usec(void)
{
	suseconds_t		usec;
	struct timeval	*time;

	usec = 0;
	if (gettimeofday(time, NULL) == -1)
		return (usec);
	usec = time->tv_usec;
	return (usec);
}

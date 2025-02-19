/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stavation_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:55:56 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/02/18 03:11:42 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "../../includes/philosophers.h"

int	check_philo_starvation(t_philo_ctx *ctx, suseconds_t last_dining_usec)
{
	long		starvation_time;
	suseconds_t	current_time_usec;

	starvation_time = ctx->time_to_die * MS_TO_USEC;
	current_time_usec = retrive_current_usec();
	if (current_time_usec - last_dining_usec >= starvation_time)
		return (1);
	else
		return (0);
}

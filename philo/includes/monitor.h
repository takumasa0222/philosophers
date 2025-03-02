/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:56:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/03/02 18:58:55 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H
# include "./philosophers.h"

void	*start_monitor_thread(void *arg);
void	check_starvation(t_philo_ctx *shared, long now);
void	set_stop(t_philo_ctx *shared);
int		is_stopped(t_philo_ctx *shared);
#endif
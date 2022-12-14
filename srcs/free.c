/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:55:30 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/05 14:41:26 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_allocs(pthread_t *phi, pthread_t *deaths, t_stru *stru, int mod)
{
	if (mod == 0)
		free(phi);
	if (mod == 1)
		free(deaths);
	if (mod == 2)
	{
		free(phi);
		free(deaths);
	}
	if (stru->start_eat)
		free(stru->start_eat);
	else
		return (1);
	if (stru->mutex)
		free(stru->mutex);
	return (1);
}

int	free_destroy(t_stru *stru, pthread_t *philos, pthread_t *deaths)
{
	pthread_mutex_destroy(&stru->mic);
	pthread_mutex_destroy(&stru->meal);
	pthread_mutex_destroy(&stru->i_lock);
	pthread_mutex_destroy(&stru->seat_lock);
	pthread_mutex_destroy(&stru->atel_lock);
	return (free_allocs(philos, deaths, stru, 2));
}

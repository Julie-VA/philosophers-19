/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:55:30 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/27 14:34:30 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_allocs(pthread_t *philos, t_stru *stru)
{
	free(philos);
	if (stru->start_eat)
		free(stru->start_eat);
	else
		return (1);
	if (stru->mutex)
		free(stru->mutex);
	return (1);
}
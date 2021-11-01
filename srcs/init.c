/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:37:10 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/01 14:38:08 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc(pthread_t **philos, pthread_t **deaths, t_stru *stru)
{
	*philos = malloc(sizeof(pthread_t) * stru->args.phi_count);
	if (!philos)
		return (1);
	*deaths = malloc(sizeof(pthread_t) * stru->args.phi_count);
	if (!deaths)
		return (free_allocs(*philos, NULL, stru, 0));
	stru->start_eat = malloc(sizeof(UL) * stru->args.phi_count);
	if (!stru->start_eat)
		return (free_allocs(*philos, *deaths, stru, 2));
	stru->mutex = malloc(sizeof(pthread_mutex_t) * stru->args.phi_count);
	if (!stru->mutex)
		return (free_allocs(*philos, *deaths, stru, 2));
	return (0);
}

int	create(t_stru *stru, pthread_t *philos, pthread_t *deaths)
{
	int	i;

	i = 0;
	while (i < stru->args.phi_count)
	{
		stru->index = i + 1;
		pthread_mutex_init(&stru->mutex[i], NULL);
		pthread_mutex_lock(&stru->mutex[i]);
		if (pthread_create(&philos[i++], NULL, &philo_loop, (void *)stru) != 0)
			return (free_allocs(philos, deaths, stru, 2));
		usleep(50);
	}
	return (0);
}

int	init_threads(t_stru *stru)
{
	int			i;
	pthread_t	*philos;
	pthread_t	*deaths;

	stru->meals_count = 0;
	stru->dead = 0;
	philos = NULL;
	deaths = NULL;
	if (alloc(&philos, &deaths, stru))
		return (1);
	pthread_mutex_init(&stru->mic, NULL);
	pthread_mutex_init(&stru->meal, NULL);
	if (create(stru, philos, deaths))
		return (1);
	stru->time_start = get_time();
	i = 0;
	while (i < stru->args.phi_count)
		pthread_mutex_unlock(&stru->mutex[i++]);
	i = 0;
	while (i < stru->args.phi_count)
	{
		stru->index = i + 1;
		if (pthread_create(&deaths[i++], NULL, &death_loop, (void *)stru) != 0)
			return (free_allocs(philos, deaths, stru, 2));
		usleep(50);
	}
	i = 0;
	while (i < stru->args.phi_count)
	{
		pthread_mutex_destroy(&stru->mutex[i]);
		if (pthread_join(philos[i++], NULL) != 0)
			return (free_allocs(philos, deaths, stru, 2));
	}
	i = 0;
	while (i < stru->args.phi_count)
	{
		if (pthread_join(deaths[i++], NULL) != 0)
			return (free_allocs(philos, deaths, stru, 2));
	}
	pthread_mutex_destroy(&stru->mic);
	pthread_mutex_destroy(&stru->meal);
	free_allocs(philos, deaths, stru, 2);
	return (0);
}

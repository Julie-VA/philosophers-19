/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:37:10 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/02 18:52:43 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_alloc(pthread_t **philos, pthread_t **deaths, t_stru *stru)
{
	stru->meals_count = 0;
	stru->dead = 0;
	stru->ate_last = 0;
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

static int	create_phi(t_stru *stru, pthread_t *philos, pthread_t *deaths)
{
	int	i;

	i = 0;
	while (i < stru->args.phi_count)
	{
		pthread_mutex_lock(&stru->i_lock);
		stru->index = i + 1;
		pthread_mutex_unlock(&stru->i_lock);
		pthread_mutex_init(&stru->mutex[i], NULL);
		pthread_mutex_lock(&stru->mutex[i]);
		if (pthread_create(&philos[i++], NULL, &philo_loop, (void *)stru) != 0)
			return (free_destroy(stru, philos, deaths));
		usleep(50);
	}
	return (0);
}

static int	create_deaths(t_stru *stru, pthread_t *philos, pthread_t *deaths)
{
	int	i;

	i = 0;
	while (i < stru->args.phi_count)
	{
		pthread_mutex_lock(&stru->i_lock);
		stru->index = i + 1;
		pthread_mutex_unlock(&stru->i_lock);
		if (pthread_create(&deaths[i++], NULL, &death_loop, (void *)stru) != 0)
			return (free_destroy(stru, philos, deaths));
		usleep(50);
	}
	return (0);
}

static int	join(t_stru *stru, pthread_t *philos, pthread_t *deaths, int mod)
{
	int	i;

	i = 0;
	if (mod)
	{
		while (i < stru->args.phi_count)
		{
			pthread_mutex_destroy(&stru->mutex[i]);
			if (pthread_join(philos[i++], NULL) != 0)
				return (free_destroy(stru, philos, deaths));
		}	
	}
	else
	{
		while (i < stru->args.phi_count)
		{
			if (pthread_join(deaths[i++], NULL) != 0)
				return (free_destroy(stru, philos, deaths));
		}
	}
	return (0);
}

int	init_threads(t_stru *stru)
{
	int			i;
	pthread_t	*philos;
	pthread_t	*deaths;

	philos = NULL;
	deaths = NULL;
	if (init_alloc(&philos, &deaths, stru))
		return (1);
	pthread_mutex_init(&stru->mic, NULL);
	pthread_mutex_init(&stru->meal, NULL);
	pthread_mutex_init(&stru->i_lock, NULL);
	pthread_mutex_init(&stru->seat_lock, NULL);
	if (create_phi(stru, philos, deaths))
		return (1);
	stru->time_start = get_time();
	i = 0;
	while (i < stru->args.phi_count)
		pthread_mutex_unlock(&stru->mutex[i++]);
	if (create_deaths(stru, philos, deaths))
		return (1);
	if (join(stru, philos, deaths, 0))
		return (1);
	if (join(stru, philos, deaths, 1))
		return (1);
	free_destroy(stru, philos, deaths);
	return (0);
}

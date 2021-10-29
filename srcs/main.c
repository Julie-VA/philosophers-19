/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/29 14:06:57 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_loop(void *tmp)
{
	t_stru	*stru;
	int		index;

	stru = (t_stru *)tmp;
	index = stru->index;
	pthread_mutex_lock(&stru->mutex[index - 1]);
	pthread_mutex_unlock(&stru->mutex[index - 1]);
	if (index % 2 == 0)
	{
		p_think(stru, index);
		usleep(stru->args.t_eat / 2);
	}
	while (1)
	{
		if (take_forks(stru, index))
			break ;
		if (p_eat(stru, index))
			break ;
		if (p_sleep(stru, index))
			break ;
		if (p_think(stru, index))
			break ;
	}
	pthread_mutex_unlock(&stru->mic);
	return (NULL);
}

static void	*death_loop(void *tmp)
{
	t_stru	*stru;
	int		index;

	stru = (t_stru *)tmp;
	index = stru->index;
	stru->start_eat[index - 1] = 0;
	while (!stru->start_eat[index - 1] && !stru->dead)
		;
	while (1)
	{
		if (stru->dead || get_time() - stru->start_eat[index - 1] > (unsigned long)stru->args.t_die)
		{
			if (stru->dead)
				break ;
			write_action(index, DIE, stru, 1);
			break ;
		}
		usleep(100);
	}
	stru->dead = 1;
	return (NULL);
}

static int	init_threads(t_stru *stru)
{
	int			i;
	pthread_t	*philos;
	pthread_t	*deaths;

	if (stru->args.phi_count == 1)
	{
		printf("0 1 has taken a fork\n%d 1 is dead\n", stru->args.t_die);
		return (0);
	}
	philos = malloc(sizeof(pthread_t) * stru->args.phi_count);
	if (!philos)
		return (1);
	deaths = malloc(sizeof(pthread_t) * stru->args.phi_count);
	if (!deaths)
		return (free_allocs(philos, NULL, stru, 0));
	stru->start_eat = malloc(sizeof(unsigned long) * stru->args.phi_count);
	if (!stru->start_eat)
		return (free_allocs(philos, deaths, stru, 2));
	stru->mutex = malloc(sizeof(pthread_mutex_t) * stru->args.phi_count);
	if (!stru->mutex)
		return (free_allocs(philos, deaths, stru, 2));
	stru->dead = 0;
	pthread_mutex_init(&stru->mic, NULL);
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
	i = 0;
	stru->time_start = get_time();
	while (i < stru->args.phi_count)
	{
		pthread_mutex_unlock(&stru->mutex[i++]);
	}
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
	free_allocs(philos, deaths, stru, 2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stru		stru;

	if (set_args(argc, argv, &stru.args))
		return (1);
	if (init_threads(&stru))
		return (1);
	system("leaks philo");
	return (0);
}

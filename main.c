/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/21 17:06:54 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*test(void *tmp)
{
	t_stru	*stru;
	int		index;
	unsigned long	start_eat;

	stru = (t_stru *)tmp;
	index = stru->index;
	start_eat = 0;
	stru->die = 0;
	while (!stru->start)
		;
	while (1)
	{
		if (stru->args.t_die < stru->args.t_eat && !stru->die)
		{
			start_eat = get_time();
			printf("%ld %d manj\n", get_time() - stru->time_start, index);
			usleep((stru->args.t_die) * 1000);
			printf("%ld %d ded\n", get_time() - stru->time_start, index);
			stru->die = 1;
			break ;
		}
		else
		{
			start_eat = get_time();
			printf("%ld %d manj\n", get_time() - stru->time_start, index);
			usleep(stru->args.t_eat * 1000);
		}
		printf("%ld %d dor\n", get_time() - stru->time_start, index);
		usleep(stru->args.t_sleep * 1000);
		if (get_time() - start_eat > (unsigned long)stru->args.t_die)
		{
			printf("%ld %d ded\n", get_time() - stru->time_start, index);
			break ;
		}
	}
	return (NULL);
}

static int	init_threads(t_stru *stru)
{
	int			i;
	pthread_t	*philos;

	philos = malloc(sizeof(pthread_t) * stru->args.phi_count);
	if (!philos)
		return (1);
	stru->mutex = malloc(sizeof(pthread_mutex_t) * stru->args.phi_count);
	if (!stru->mutex)
		return (free_allocs(philos, stru));
	stru->start = 0;
	i = 0;
	while (i < stru->args.phi_count)
	{
		stru->index = i;
		pthread_mutex_init(&stru->mutex[i], NULL);
		if (pthread_create(&philos[i++], NULL, &test, (void *)stru) != 0)
			return (free_allocs(philos, stru));
		usleep(50);
	}
	stru->time_start = get_time();
	stru->start = 1;
	i = 0;
	while (i < stru->args.phi_count)
	{
		pthread_mutex_destroy(&stru->mutex[i]);
		if (pthread_join(philos[i++], NULL) != 0)
			return (free_allocs(philos, stru));
	}
	free(philos);
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

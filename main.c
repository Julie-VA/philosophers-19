/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/26 11:35:56 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_action(unsigned long time, int index, char *action, t_stru *stru)
{
	char	*str;
	char	*tmp;
	char	*bis;

	pthread_mutex_lock(&stru->mic);
	tmp = ft_itoa(time);
	str = mod_strjoin(tmp, "", 0);
	free(tmp);
	tmp = ft_itoa(index);
	bis = mod_strjoin(str, tmp, 0);
	free(tmp);
	free(str);
	str = mod_strjoin(bis, action, 1);
	free(bis);
	write(1, str, ft_strlen(str));
	free(str);
	pthread_mutex_unlock(&stru->mic);
}

static void	*philo_loop(void *tmp)
{
	t_stru	*stru;
	int		index;
	unsigned long	start_eat;

	stru = (t_stru *)tmp;
	index = stru->index;
	start_eat = 0;
	stru->dead = 0;
	while (!stru->start)
		;
	if (index % 2 == 0)
	{
		p_think(stru, index);
		usleep(800);
	}
	while (1)
	{
		take_forks(stru, index);
		if (p_eat(stru, index, &start_eat))
			break ;
		p_sleep(stru, index);
		if (p_die(stru, index, start_eat))
			break ;
		p_think(stru, index);
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
	pthread_mutex_init(&stru->mic, NULL);
	i = 0;
	while (i < stru->args.phi_count)
	{
		stru->index = i + 1;
		pthread_mutex_init(&stru->mutex[i], NULL);
		if (pthread_create(&philos[i++], NULL, &philo_loop, (void *)stru) != 0)
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

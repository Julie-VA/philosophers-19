/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/26 17:39:23 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_loop(unsigned long t, t_stru *stru)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < t)
		usleep(stru->args.phi_count * 2);
}

void	write_action(int index, char *action, t_stru *stru, int dead_msg)
{
	char	*str;
	char	*tmp;
	char	*bis;

	pthread_mutex_lock(&stru->mic);
	tmp = ft_itoa(get_time() - stru->time_start);
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
	if (!dead_msg)
		pthread_mutex_unlock(&stru->mic);
}

static void	*philo_loop(void *tmp)
{
	t_stru			*stru;
	int				index;
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
		if (take_forks(stru, index))
			break ;
		if (p_eat(stru, index, &start_eat))
			break ;
		if (p_sleep(stru, index))
			break ;
		if (p_die(stru, index, start_eat))
			break ;
		if (p_think(stru, index))
			break ;
	}
	pthread_mutex_unlock(&stru->mic);
	return (NULL);
}

static int	init_threads(t_stru *stru)
{
	int			i;
	pthread_t	*philos;

	if (stru->args.phi_count == 1)
	{
		printf("0 1 has taken a fork\n%d 1 is dead\n", stru->args.t_die);
		return (0);
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/02 16:50:43 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_first(int loop, int index, t_stru *stru)
{
	if (!loop && index % 2 == 0)
	{
		if (stru->args.phi_count < 100)
			usleep(800);
		else if (stru->args.phi_count < 150)
			usleep(1200);
		else
			usleep(1600);
	}
	return (1);
}

void	*philo_loop(void *tmp)
{
	t_stru	*stru;
	int		index;
	int		loop;

	stru = (t_stru *)tmp;
	pthread_mutex_lock(&stru->i_lock);
	index = stru->index;
	pthread_mutex_unlock(&stru->i_lock);
	loop = 0;
	pthread_mutex_lock(&stru->mutex[index - 1]);
	pthread_mutex_unlock(&stru->mutex[index - 1]);
	while (1)
	{
		pthread_mutex_lock(&stru->meal);
		if (stru->args.eat_times >= 0
			&& stru->meals_count >= stru->args.eat_times * stru->args.phi_count)
		{
			pthread_mutex_unlock(&stru->meal);
			break ;
		}
		pthread_mutex_unlock(&stru->meal);
		if (p_think(stru, index))
			break ;
		loop = wait_first(loop, index, stru);
		if (take_forks(stru, index))
			break ;
		if (p_eat(stru, index))
			break ;
		if (p_sleep(stru, index))
			break ;
	}
	return (NULL);
}

static void	init_vars(t_stru *stru, int *index)
{
	pthread_mutex_lock(&stru->i_lock);
	*index = stru->index;
	pthread_mutex_unlock(&stru->i_lock);
	pthread_mutex_lock(&stru->seat_lock);
	stru->start_eat[*index - 1] = get_time();
	pthread_mutex_unlock(&stru->seat_lock);
}

void	*death_loop(void *tmp)
{
	t_stru	*stru;
	int		index;

	stru = (t_stru *)tmp;
	init_vars(stru, &index);
	while (!stru->start_eat[index - 1] && !stru->dead)
		;
	while (1)
	{
		pthread_mutex_lock(&stru->meal);
		if (stru->args.eat_times >= 0
			&& stru->meals_count >= stru->args.eat_times * stru->args.phi_count)
		{
			pthread_mutex_unlock(&stru->meal);
			return (NULL);
		}
		pthread_mutex_unlock(&stru->meal);
		pthread_mutex_lock(&stru->seat_lock);
		pthread_mutex_lock(&stru->dead_lock);
		if (stru->dead
			|| get_time() - stru->start_eat[index - 1] > (UL)stru->args.t_die)
		{
			pthread_mutex_unlock(&stru->dead_lock);
			pthread_mutex_unlock(&stru->seat_lock);
			pthread_mutex_lock(&stru->dead_lock);
			if (stru->dead)
			{
				pthread_mutex_unlock(&stru->dead_lock);
				break ;
			}
			pthread_mutex_unlock(&stru->dead_lock);
			write_action(index, DIE, stru, 1);
			pthread_mutex_lock(&stru->dead_lock);
			stru->dead = 1;
			pthread_mutex_unlock(&stru->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&stru->dead_lock);
		pthread_mutex_unlock(&stru->seat_lock);
		usleep(50);
	}
	pthread_mutex_unlock(&stru->mic);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_stru		stru;

	if (set_args(argc, argv, &stru.args))
		return (1);
	if (!stru.args.phi_count)
		return (0);
	if (stru.args.phi_count == 1)
	{
		printf("0 1 has taken a fork\n%d 1 is dead\n", stru.args.t_die);
		return (0);
	}
	if (init_threads(&stru))
		return (1);
	return (0);
}

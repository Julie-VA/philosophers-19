/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:04:42 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/02 19:11:29 by rvan-aud         ###   ########.fr       */
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

static int	p_loop_core(t_stru *stru, int index, int loop)
{
	if (stru->args.eat_times >= 0
		&& stru->meals_count >= stru->args.eat_times * stru->args.phi_count)
		return (1);
	if (p_think(stru, index))
		return (1);
	loop = wait_first(loop, index, stru);
	if (take_forks(stru, index))
		return (1);
	if (p_eat(stru, index))
		return (1);
	if (p_sleep(stru, index))
		return (1);
	return (0);
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
		if (p_loop_core(stru, index, loop))
			break ;
	}
	return (NULL);
}

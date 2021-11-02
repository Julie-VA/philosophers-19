/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:05:28 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/02 19:11:15 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_vars(t_stru *stru, int *index)
{
	pthread_mutex_lock(&stru->i_lock);
	*index = stru->index;
	pthread_mutex_unlock(&stru->i_lock);
	pthread_mutex_lock(&stru->seat_lock);
	stru->start_eat[*index - 1] = get_time();
	pthread_mutex_unlock(&stru->seat_lock);
}

static int	d_loop_core(t_stru *stru, int index)
{
	if (stru->args.eat_times >= 0
		&& stru->meals_count >= stru->args.eat_times * stru->args.phi_count)
		return (-1);
	pthread_mutex_lock(&stru->seat_lock);
	if (stru->dead
		|| get_time() - stru->start_eat[index - 1] > (UL)stru->args.t_die)
	{
		pthread_mutex_unlock(&stru->seat_lock);
		if (stru->dead)
			return (1);
		write_action(index, DIE, stru, 1);
		stru->dead = 1;
		return (1);
	}
	pthread_mutex_unlock(&stru->seat_lock);
	usleep(100);
	return (0);
}

void	*death_loop(void *tmp)
{
	t_stru	*stru;
	int		index;
	int		ret;

	stru = (t_stru *)tmp;
	init_vars(stru, &index);
	while (!stru->start_eat[index - 1] && !stru->dead)
		;
	while (1)
	{
		ret = d_loop_core(stru, index);
		if (ret == -1)
			return (NULL);
		else if (ret == 1)
			break ;
	}
	pthread_mutex_unlock(&stru->mic);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:44:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/02 16:58:24 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_stru *stru, int index)
{
	pthread_mutex_lock(&stru->seat_lock);
	stru->start_eat[index - 1] = get_time();
	pthread_mutex_unlock(&stru->seat_lock);
	if (stru->dead)
	{			
		drop_forks(stru, index);
		return (1);
	}
	pthread_mutex_lock(&stru->meal);
	stru->meals_count++;
	pthread_mutex_unlock(&stru->meal);
	write_action(index, EAT, stru, 0);
	wait_loop(stru->args.t_eat, stru);
	drop_forks(stru, index);
	return (0);
}

int	p_sleep(t_stru *stru, int index)
{
	if (stru->dead)
		return (1);
	if (stru->args.eat_times >= 0
		&& stru->meals_count >= stru->args.eat_times * stru->args.phi_count)
		return (0);
	write_action(index, SLEEP, stru, 0);
	wait_loop(stru->args.t_sleep, stru);
	return (0);
}

int	p_think(t_stru *stru, int index)
{
	if (stru->dead)
		return (1);
	if (stru->args.eat_times >= 0
		&& stru->meals_count >= stru->args.eat_times * stru->args.phi_count)
		return (0);
	write_action(index, THINK, stru, 0);
	return (0);
}

int	take_forks(t_stru *stru, int index)
{
	pthread_mutex_lock(&stru->mutex[index - 1]);
	if (stru->dead)
	{
		pthread_mutex_unlock(&stru->mutex[index - 1]);
		return (1);
	}
	write_action(index, FORK, stru, 0);
	pthread_mutex_lock(&stru->mutex[index % stru->args.phi_count]);
	if (stru->dead)
	{
		drop_forks(stru, index);
		return (1);
	}
	write_action(index, FORK, stru, 0);
	return (0);
}

void	drop_forks(t_stru *stru, int index)
{
	pthread_mutex_unlock(&stru->mutex[index - 1]);
	pthread_mutex_unlock(&stru->mutex[index % stru->args.phi_count]);
}

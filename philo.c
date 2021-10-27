/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:44:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/27 14:32:09 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_stru *stru, int index)
{
	if (stru->args.t_die < stru->args.t_eat)
	{
		if (stru->dead)
		{
			drop_forks(stru, index);
			return (1);
		}
		write_action(index, EAT, stru, 0);
		wait_loop(stru->args.t_die, stru);
		drop_forks(stru, index);
		if (stru->dead)
			return (1);
		stru->dead = 1;
		write_action(index, DIE, stru, 1);
		return (1);
	}
	else
	{
		stru->start_eat[index] = get_time();
		if (stru->dead)
		{
			drop_forks(stru, index);
			return (1);
		}
		write_action(index, EAT, stru, 0);
		wait_loop(stru->args.t_eat, stru);
		drop_forks(stru, index);
	}
	return (0);
}

int	p_sleep(t_stru *stru, int index, unsigned long start_eat)
{
	if ((unsigned long)stru->args.t_die < stru->args.t_sleep + (get_time() - start_eat))
	{
		if (stru->dead)
			return (1);
		write_action(index, SLEEP, stru, 0);
		wait_loop(stru->args.t_die - stru->args.t_eat, stru);
		if (stru->dead)
			return (1);
		stru->dead = 1;
		write_action(index, DIE, stru, 1);
		return (1);
	}
	else
	{
		if (stru->dead)
			return (1);
		write_action(index, SLEEP, stru, 0);
		wait_loop(stru->args.t_sleep, stru);
	}
	return (0);
}

int	p_die(t_stru *stru, int index, unsigned long start_eat)
{
	if (get_time() - start_eat > (unsigned long)stru->args.t_die)
	{	
		if (stru->dead)
			return (1);
		stru->dead = 1;
		write_action(index, DIE, stru, 1);
		return (1);
	}
	return (0);
}

int	p_think(t_stru *stru, int index)
{
	if (stru->dead)
		return (1);
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
	pthread_mutex_lock(&stru->mutex[index]);
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
	pthread_mutex_unlock(&stru->mutex[index]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:44:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/26 11:37:11 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_stru *stru, int index, unsigned long *start_eat)
{
	if (stru->args.t_die < stru->args.t_eat)
	{
		write_action(get_time() - stru->time_start, index, EAT, stru);
		usleep((stru->args.t_eat));
		pthread_mutex_unlock(&stru->mutex[index]);
		pthread_mutex_unlock(&stru->mutex[index + 1]);
		if (stru->dead)
			return (1);
		stru->dead = 1;
		write_action(get_time() - stru->time_start, index, DIE, stru);
		return (1);
	}
	else
	{
		*start_eat = get_time();
		write_action(get_time() - stru->time_start, index, EAT, stru);
		usleep(stru->args.t_eat);
		pthread_mutex_unlock(&stru->mutex[index - 1]);
		pthread_mutex_unlock(&stru->mutex[index]);
	}
	return (0);
}

void	p_sleep(t_stru *stru, int index)
{
	write_action(get_time() - stru->time_start, index, SLEEP, stru);
	usleep(stru->args.t_sleep);
}

int	p_die(t_stru *stru, int index, unsigned long start_eat)
{
	if (get_time() - start_eat > (unsigned long)stru->args.t_die)
	{
		if (stru->dead)
			return (1);
		stru->dead = 1;
		write_action(get_time() - stru->time_start, index, DIE, stru);
		return (1);
	}
	return (0);
}

void	p_think(t_stru *stru, int index)
{
	write_action(get_time() - stru->time_start, index, THINK, stru);
}

void	take_forks(t_stru *stru, int index)
{
	pthread_mutex_lock(&stru->mutex[index - 1]);
	write_action(get_time() - stru->time_start, index, FORK, stru);
	pthread_mutex_lock(&stru->mutex[index]);
	write_action(get_time() - stru->time_start, index, FORK, stru);
}
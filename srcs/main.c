/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/02 15:15:07 by rvan-aud         ###   ########.fr       */
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
		if (stru->args.eat_times >= 0
			&& stru->meals_count >= stru->args.eat_times * stru->args.phi_count)
			break ;
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
	stru->start_eat[*index - 1] = get_time();
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
		if (stru->args.eat_times >= 0
			&& stru->meals_count >= stru->args.eat_times * stru->args.phi_count)
			return (NULL);
		if (stru->dead
			|| get_time() - stru->start_eat[index - 1] > (UL)stru->args.t_die)
		{
			if (stru->dead)
				break ;
			write_action(index, DIE, stru, 1);
			stru->dead = 1;
			break ;
		}
		usleep(100);
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

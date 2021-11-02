/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:43:37 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/01 15:11:12 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

UL	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void	wait_loop(UL t, t_stru *stru)
{
	UL	start;

	start = get_time();
	while (get_time() - start < t && !stru->dead)
		usleep(stru->args.phi_count * 2);
}

void	write_action(int index, char *action, t_stru *stru, int dead_msg)
{
	char	*str;
	char	*tmp;
	char	*bis;

	pthread_mutex_lock(&stru->mic);
	if (stru->dead)
	{
		pthread_mutex_unlock(&stru->mic);
		return ;
	}
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

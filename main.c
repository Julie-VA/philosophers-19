/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/15 17:09:24 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*test(void *tmp)
{
	t_stru	*stru;

	stru = (t_stru *)tmp;
	printf("%d\n", stru->index);
	return (NULL);
}

static int	init_threads(t_stru *stru)
{
	int			i;
	pthread_t	*philos;

	philos = malloc(sizeof(pthread_t) * (stru->args.phi_count));
	if (!philos)
		return (1);
	i = 0;
	while (i < stru->args.phi_count)
	{
		stru->index = i;
		pthread_create(&philos[i++], NULL, &test, (void *)stru);
		usleep(800);
	}
	i = 0;
	while (i < stru->args.phi_count)
		pthread_join(philos[i++], NULL);
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

// pthread_t	t1;
// if (pthread_create(&t1, NULL, &test, NULL) != 0)
// 	return (1); //error
// if (pthread_join(t1, NULL) != 0)
// 	return (1); //error
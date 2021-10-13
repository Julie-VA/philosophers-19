/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/13 17:43:57 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	init_args(t_args *args)
{
	args->phi_count = -1;
	args->t_die = -1;
	args->t_eat = -1;
	args->t_sleep = -1;
	args->t_eat_times = -1;
}

int	set_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: must have 4 or 5 arguments\n");
		return (1);
	}
	init_args(args);
	if (isnumber(argv[1]))
		args->phi_count = ft_atoi(argv[1]);
	if (isnumber(argv[2]))
		args->t_die = ft_atoi(argv[2]);
	if (isnumber(argv[3]))
		args->t_eat = ft_atoi(argv[3]);
	if (isnumber(argv[4]))
		args->t_sleep = ft_atoi(argv[4]);
	if (argv[5] && isnumber(argv[5]))
		args->t_eat_times = ft_atoi(argv[5]);
	if (args->phi_count < 0 || args->t_die < 0 || args->t_eat < 0
		|| args->t_sleep < 0 || (args->t_eat_times < 0 && argv[5])
		|| args->phi_count > 200 || args->t_die < 60 || args->t_eat < 60
		|| args->t_sleep < 60)
	{
		printf("Error: bad argument(s)\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		args;
	// pthread_t	t1;

	if (set_args(argc, argv, &args))
		return (1);
	// if (pthread_create(&t1, NULL, &test, NULL) != 0)
	// 	return (1); //error
	// if (pthread_join(t1, NULL) != 0)
	// 	return (1); //error
	return (0);
}

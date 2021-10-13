/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:20 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/13 12:14:28 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

t_args	set_args(char **argv)
{
	t_args	args;

	args.phi_count = ft_atoi(argv[1]);
	args.t_die = ft_atoi(argv[2]);
	args.t_eat = ft_atoi(argv[3]);
	args.t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args.t_eat_times = ft_atoi(argv[5]);
	else
		args.t_eat_times = 0;
	return (args);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc < 5 || argc > 6)
	{
		printf("Error: bad arguments\n");
		return (1);
	}
	args = set_args(argv);
	printf("phi_count = %d\n", args.phi_count);
	printf("t_die = %d\n", args.t_die);
	printf("t_eat = %d\n", args.t_eat);
	printf("t_sleep = %d\n", args.t_sleep);
	printf("t_eat_times = %d\n", args.t_eat_times);
	return (0);
}

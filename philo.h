/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:35 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/15 17:05:24 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_args
{
	int	phi_count;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	t_eat_times;	
}	t_args;

typedef struct s_stru
{
	t_args	args;
	int		index;
}	t_stru;


int	ft_atoi(const char *nptr);
int	isnumber(char *str);
int	set_args(int argc, char **argv, t_args *args);

#endif

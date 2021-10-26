/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:35 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/26 15:14:40 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_args
{
	int	phi_count;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	eat_times;
}	t_args;

typedef struct s_stru
{
	t_args			args;
	int				index;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mic;
	int				start;
	int				dead;
	unsigned long	time_start;
}	t_stru;


int				ft_atoi(const char *nptr);
int				isnumber(char *str);
int				set_args(int argc, char **argv, t_args *args);
int				free_allocs(pthread_t *philos, t_stru *stru);
unsigned long	get_time(void);
int				ft_strlen(const char *s);
char			*ft_itoa(int value);
char			*mod_strjoin(char const *s1, char const *s2, int mod);
void			write_action(int index, char *action, t_stru *stru);
int				p_eat(t_stru *stru, int index, unsigned long *start_eat);
void			p_sleep(t_stru *stru, int index);
int				p_die(t_stru *stru, int index, unsigned long start_eat);
void			p_think(t_stru *stru, int index);
void			take_forks(t_stru *stru, int index);
void			wait_loop(unsigned long t, t_stru *stru);

#endif

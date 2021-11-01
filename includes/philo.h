/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:51:35 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/01 14:38:25 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define UL unsigned long

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
	int				dead;
	int				meals_count;
	unsigned long	*start_eat;
	unsigned long	time_start;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mic;
	pthread_mutex_t	meal;
}	t_stru;

int		ft_atoi(const char *nptr);
int		isnumber(char *str);
int		set_args(int argc, char **argv, t_args *args);
int		free_allocs(pthread_t *phi, pthread_t *deaths, t_stru *stru, int mod);
UL		get_time(void);
int		ft_strlen(const char *s);
char	*ft_itoa(int value);
char	*mod_strjoin(char const *s1, char const *s2, int mod);
void	write_action(int index, char *action, t_stru *stru, int dead_msg);
int		p_eat(t_stru *stru, int index);
int		p_sleep(t_stru *stru, int index);
int		p_die(t_stru *stru, int index);
int		p_think(t_stru *stru, int index);
int		take_forks(t_stru *stru, int index);
void	drop_forks(t_stru *stru, int index);
void	wait_loop(unsigned long t, t_stru *stru);
int		alloc(pthread_t **philos, pthread_t **deaths, t_stru *stru);
int		create(t_stru *stru, pthread_t *philos, pthread_t *deaths);
void	*philo_loop(void *tmp);
void	*death_loop(void *tmp);
int		init_threads(t_stru *stru);

#endif

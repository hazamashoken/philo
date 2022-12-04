/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:03:28 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/03 20:44:05 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# include "philo_define.h"

typedef struct s_input
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_eat;
}					t_input;

typedef struct s_fork
{
	int				left;
	int				right;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				num_of_times_ate;
	long long		time_to_die;
	t_fork			fork;
	pthread_t		thread;
}					t_philo;

typedef struct s_env
{
	int				n_thread;
	int				philo_dead;
	long long		t0;
	t_input			input;
	t_philo			*philo;
	pthread_t		checker;
	pthread_mutex_t	*forks;
	pthread_mutex_t	table;
	pthread_mutex_t	write;
}					t_env;

//libft.c
int			ft_atoi(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(const char *str);
void		env_free(t_env *env);

//check_args.c
int			check_args(int argc, char **argv, t_env *env);

//philophile.c
int			create_philos(t_env *env);

//thread_lightly.c
int			create_threads(t_env *env);
int			destory_threads(t_env *env);

//what_time_is_it.c
long long	get_time(void);
long long	delta_time(long long time);
void		my_usleep(long long time, t_env *env);

//fork_you.c
void		unlock_forks(t_env *env);
int			create_forks(t_env *env);

//eat_think_sleep_die.c
int			philo_think(t_env *env, int i);
int			philo_sleep(t_env *env, int i);
int			philo_eat(t_env *env, int i);
int			are_you_dead(t_env *env, int *i);

//simon_say.c
int			philo_print(t_env *env, int id, char *status, char *color);

//routine.c
void		*routine(void *args);
void		*anyone_die_yet(void *args);

#endif

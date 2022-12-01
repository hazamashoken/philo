/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:40:19 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 14:54:38 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# include "philo_define.h"

typedef struct s_input
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
}	t_input;

typedef struct s_philo
{
	int				id;
	int				died;
	int				eat_count;
	long long		time_to_die;
	pthread_t		thread;
}					t_philo;

typedef struct s_env
{
	int				philo_dead;
	long long		t0;
	t_input			input;
	pid_t			*pid;
	t_philo			philo;
	sem_t			*forks;
	sem_t			*table;
	sem_t			*print;
}					t_env;

//sem.c
int			create_semaphores(t_env *env);

//input.c
int			parse_input(t_env *env, int argc, char **argv);

//init.c
void		init_env(t_env *env);

//time.c
long long	delta_time(long long time);
long long	get_time(void);
int			my_sleep(t_env *env, int time);

//exit_handle.c
int			exit_failure(t_env *env);

//routine.c
void		routine(t_env *env);

//philo_utils.c
int			ft_atoi(char *str);
int			ft_checkset(char *str, char *set);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:40:19 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 03:04:55 by tliangso         ###   ########.fr       */
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
	int				n_process;
	int				philo_dead;
	long long		t0;
	t_input			input;
	pid_t			*pid;
	t_philo			philo;
	sem_t			*forks;
	sem_t			*table;
	sem_t			*print;
}					t_env;

//check_args_bonus.c
int			philo_think_bonus(t_env *env, int i);
int			philo_sleep_bonus(t_env *env, int i);
int			philo_eat_bonus(t_env *env, int i);
int			are_you_dead_yet(t_env *env);
int			philo_print_bonus(t_env *env,
				int id, char *status, char *color);

//what_time_is_it.c
long long	get_time(void);
long long	delta_time(long long time);
void		exec_action(long long time);
void		my_usleep(long long time);

//philo_utils.c
int			ft_atoi(char *str);
int			ft_checkset(char *str, char *set);

#endif

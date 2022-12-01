/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:40:19 by tliangso          #+#    #+#             */
/*   Updated: 2022/11/11 12:58:10 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>

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
	int				eat_count;
	long long		time_to_die;
	int				alive;
}					t_philo;

typedef struct s_env
{
	int				philo_dead;
	long long		t0;
	t_input			input;
	pid_t			*pid;
	t_philo			philo;
	pthread_t		checker;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*stop;
	sem_t			*dead;
	sem_t			*eat;
}					t_env;

//check_args_bonus.c
int			check_args_bonus(int argc, char **argv, t_env *env);
void		philo_think_bonus(t_env *env, int i);
void		philo_sleep_bonus(t_env *env, int i);
int			philo_eat_bonus(t_env *env, int i);
int			are_you_dead_yet(t_env*env);
void		philo_print_bonus(t_env *env,
				int id, char *status, char *color);
//what_time_is_it.c
long long	get_time(void);
long long	delta_time(long long time);
void		exec_action(long long time);
void		my_usleep(long long time);

//libft.c
int			ft_atoi(char *str);

#endif

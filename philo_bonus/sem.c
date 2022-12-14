/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:30:10 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 23:43:22 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sem_unlink_all(void)
{
	sem_unlink("/forks");
	sem_unlink("/table");
	sem_unlink("/print");
}

static int	sem_failure(t_env *env)
{
	if (env->forks != SEM_FAILED)
		sem_close(env->forks);
	if (env->table != SEM_FAILED)
		sem_close(env->table);
	if (env->print != SEM_FAILED)
		sem_close(env->print);
	return (EXIT_FAILURE);
}

int	create_semaphores(t_env *env)
{
	sem_unlink_all();
	env->forks = sem_open("/forks", O_CREAT, 0644, env->input.num_philo);
	env->table = sem_open("/table", O_CREAT, 0644, 1);
	env->print = sem_open("/print", O_CREAT, 0644, 1);
	if (env->forks == SEM_FAILED || env->table == SEM_FAILED
		|| env->print == SEM_FAILED)
		return (sem_failure(env));
	return (EXIT_SUCCESS);
}

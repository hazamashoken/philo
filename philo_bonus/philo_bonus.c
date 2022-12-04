/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:07:45 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/02 01:36:05 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>

int	create_process(t_env *env)
{
	int	i;

	i = 0;
	env->t0 = get_time();
	while (i < env->input.num_philo)
	{
		env->philo.id++;
		env->philo.time_to_die = get_time();
		env->pid[i] = fork();
		if (env->pid[i] == -1)
			return (EXIT_FAILURE);
		if (env->pid[i] == 0)
			routine(env);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	destroy_free_env(t_env *env)
{
	int	i;
	int	status;

	i = 0;
	while (i < env->input.num_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == PHILO_DIED)
		{
			i = 0;
			while (i < env->input.num_philo)
				kill(env->pid[i++], SIGTERM);
			break ;
		}
		i++;
	}
	if (env->forks != SEM_FAILED)
		sem_close(env->forks);
	if (env->table != SEM_FAILED)
		sem_close(env->table);
	if (env->print != SEM_FAILED)
		sem_close(env->print);
	if (env->pid != NULL)
		free(env->pid);
}

int	main(int argc, char **argv)
{
	t_env	env;

	init_env(&env);
	if (parse_input(&env, argc, argv) == EXIT_FAILURE)
		return (exit_failure(&env));
	if (create_semaphores(&env) == EXIT_FAILURE)
		return (exit_failure(&env));
	if (create_process(&env) == EXIT_FAILURE)
		return (exit_failure(&env));
	destroy_free_env(&env);
	return (EXIT_SUCCESS);
}

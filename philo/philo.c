/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:05:22 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/09 14:21:46 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	pthread_mutex_lock(&env->forks[0]);
	printf("%s%d%-8s %d %-30s%s\n",
		BLUE, 0, " ms", 1, LEFT_FORK, RESET);
	usleep(env->input.time_to_eat * 1000);
	printf("%s%d%-8s %d %-30s%s\n",
		RED, env->input.time_to_die, " ms", 1, DIED, RESET);
	return (NULL);
}

void	init_one(t_env *env)
{
	pthread_create(&env->philo[0].thread, NULL, one_philo, env);
	pthread_join(env->philo[0].thread, NULL);
	destory_threads(env);
	env_free(env);
}

void	init_env(t_env *env)
{
	env->n_thread = 0;
	env->t0 = 0;
	env->philo = NULL;
	env->checker = NULL;
	env->forks = NULL;
	env->philo_dead = FALSE;
}

int	main(int argc, char **argv)
{
	t_env	env;

	init_env(&env);
	if (check_args(argc, argv, &env) == FALSE)
		return (EXIT_FAILURE);
	if (create_philos(&env) == FALSE)
		return (EXIT_FAILURE);
	if (create_forks(&env) == FALSE)
		return (EXIT_FAILURE);
	if (env.input.num_philo == 1)
	{
		init_one(&env);
		return (EXIT_SUCCESS);
	}
	else
		if (create_threads(&env) == FALSE)
			return (EXIT_FAILURE);
	destory_threads(&env);
	env_free(&env);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:05:22 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/16 10:58:05 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_env *env)
{
	if (pthread_mutex_init(&env->write, NULL) != FALSE)
		return (FALSE);
	env->t0 = get_time();
	philo_print(env, 1, LEFT_FORK, BLUE);
	exec_action(env->input.time_to_die / 1000);
	philo_print(env, 1, DIED, RED);
	env_free(env);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (check_args(argc, argv, &env) == FALSE)
		return (EXIT_FAILURE);
	if (create_philos(&env) == FALSE)
		return (EXIT_FAILURE);
	if (create_forks(&env) == FALSE)
		return (EXIT_FAILURE);
	if (env.input.num_philo == 1)
	{
		if (one_philo(&env) == FALSE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (create_threads(&env) == FALSE)
		return (EXIT_FAILURE);
	if (destory_threads(&env) == FALSE)
		return (EXIT_FAILURE);
	env_free(&env);
	return (EXIT_SUCCESS);
}

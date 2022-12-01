/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_lightly.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:12:52 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 15:27:31 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->input.num_philo)
	{
		if (pthread_join(env->philo[i].thread, NULL) != FALSE)
			return (FALSE);
		i++;
	}
	if (pthread_join(env->checker, NULL) != FALSE)
		return (FALSE);
	return (TRUE);
}

int	destory_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->input.num_philo)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->write);
	return (TRUE);
}

int	create_threads(t_env *env)
{
	int	i;

	i = 0;
	env->philo_dead = FALSE;
	if (pthread_mutex_init(&env->write, NULL) != FALSE)
		return (FALSE);
	env->t0 = get_time();
	while (i < env->input.num_philo)
	{
		env->n_thread = i;
		if (pthread_create(&env->philo[i].thread, NULL, &routine, env) != FALSE)
			return (FALSE);
		i++;
		usleep(10);
	}
	if (pthread_create(&env->checker, NULL, &anyone_die_yet, env) != FALSE)
		return (FALSE);
	usleep(10);
	if (join_threads(env) == FALSE)
		return (FALSE);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_lightly.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:12:52 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/04 17:34:56 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->input.num_philo)
	{
		pthread_join(env->philo[i].thread, NULL);
		i++;
	}
	pthread_join(env->checker, NULL);
	printf("end\n");
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
		env->philo[i].time_to_die = get_time();
		if (pthread_create(&env->philo[i].thread, NULL, &routine, env) != FALSE)
			return (FALSE);
		i += 2;
		if (i >= env->input.num_of_times_eat && i % 2 == 0)
			i = 1;
		usleep(10);
	}
	if (pthread_create(&env->checker, NULL, &anyone_die_yet, env) != FALSE)
		return (FALSE);
	usleep(10);
	if (join_threads(env) == FALSE)
		return (FALSE);
	return (TRUE);
}

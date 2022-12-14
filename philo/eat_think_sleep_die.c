/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep_die.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:30:02 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/09 16:32:40 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	philo_think(t_env *env, int i)
{
	if (philo_print(env, env->philo[i].id, THINK, GREEN) == FALSE)
		return (pthread_mutex_unlock(&env->table), drop_forks(env, i), FALSE);
	return (TRUE);
}

int	philo_sleep(t_env *env, int i)
{
	if (philo_print(env, env->philo[i].id, SLEEP, PINK) == FALSE)
		return (pthread_mutex_unlock(&env->table), drop_forks(env, i), FALSE);
	my_usleep(env->input.time_to_sleep, env, i);
	return (TRUE);
}

int	drop_forks(t_env *env, int i)
{
	pthread_mutex_unlock(&env->forks[env->philo[i].fork.left]);
	pthread_mutex_unlock(&env->forks[env->philo[i].fork.right]);
	env->philo[i].num_of_times_ate++;
	return (TRUE);
}

int	philo_eat(t_env *env, int i)
{
	pthread_mutex_lock(&env->table);
	if (env->philo_dead)
		return (pthread_mutex_unlock(&env->table), drop_forks(env, i), FALSE);
	pthread_mutex_lock(&env->forks[env->philo[i].fork.left]);
	if (philo_print(env, env->philo[i].id, LEFT_FORK, BLUE) == FALSE)
		return (pthread_mutex_unlock(&env->table), drop_forks(env, i), FALSE);
	if (env->philo_dead)
		return (pthread_mutex_unlock(&env->table), drop_forks(env, i), FALSE);
	pthread_mutex_lock(&env->forks[env->philo[i].fork.right]);
	if (philo_print(env, env->philo[i].id, RIGHT_FORK, BLUE) == FALSE)
		return (pthread_mutex_unlock(&env->table), drop_forks(env, i), FALSE);
	pthread_mutex_unlock(&env->table);
	if (env->philo_dead)
		return (drop_forks(env, i), FALSE);
	if (philo_print(env, env->philo[i].id, EAT, YELLOW) == FALSE)
		return (pthread_mutex_unlock(&env->table), drop_forks(env, i), FALSE);
	env->philo[i].time_to_die = get_time();
	my_usleep(env->input.time_to_eat, env, i);
	drop_forks(env, i);
	return (TRUE);
}

int	are_you_dead(t_env *env, int *i)
{
	long long	time;

	if (*i == env->input.num_philo)
		*i = 0;
	time = delta_time(env->philo[*i].time_to_die);
	if (time > env->input.time_to_die)
	{
		philo_print(env, env->philo[*i].id, DIED, RED);
		env->philo_dead = TRUE;
		return (TRUE);
	}
	i++;
	return (FALSE);
}

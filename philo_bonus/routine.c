/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:39:27 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/02 01:19:10 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

static void	take_fork(t_env *env)
{
	sem_wait(env->table);
	sem_wait(env->forks);
	printf("%s%lld %d has taken a fork%s\n",
		YELLOW, delta_time(env->t0), env->philo.id, RESET);
	sem_wait(env->forks);
	printf("%s%lld %d has taken a fork%s\n",
		YELLOW, delta_time(env->t0), env->philo.id, RESET);
	sem_post(env->table);
}

static void	eat(t_env *env)
{
	take_fork(env);
	sem_post(env->print);
	printf("%s%lld %d is eating%s\n",
		GREEN, delta_time(env->t0), env->philo.id, RESET);
	sem_post(env->print);
	my_sleep(env, env->input.time_to_eat);
	env->philo.eat_count++;
}

static void	*monitor(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (env->philo.eat_count <= env->input.num_must_eat
		|| env->input.num_must_eat == -1)
	{
		if (env->philo_dead)
		{
			sem_wait(env->print);
			printf("%s%lld %d died%s\n",
				RED, delta_time(env->t0), env->philo.id, RESET);
			exit(PHILO_DIED);
		}
	}
	return (NULL);
}

void	routine(t_env *env)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &monitor, env);
	pthread_detach(thread);
	while (env->philo.eat_count < env->input.num_must_eat
		|| env->input.num_must_eat == -1)
	{
		eat(env);
		sem_post(env->forks);
		sem_post(env->forks);
		env->philo.time_to_die = get_time();
		if (!(env->philo.eat_count < env->input.num_must_eat
				|| env->input.num_must_eat == -1))
			break ;
		sem_wait(env->print);
		printf("%s%lld %d is sleeping%s\n",
			PINK, delta_time(env->t0), env->philo.id, RESET);
		sem_post(env->print);
		my_sleep(env, env->input.time_to_sleep);
		sem_wait(env->print);
		printf("%s%lld %d is thinking%s\n",
			BLUE, delta_time(env->t0), env->philo.id, RESET);
		sem_post(env->print);
	}
	exit(PHILO_DONE);
}

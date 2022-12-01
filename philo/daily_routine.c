/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:10:26 by tliangso          #+#    #+#             */
/*   Updated: 2022/11/17 23:02:27 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_execute(t_env *env, int i)
{
	if (philo_eat(env, i) == FALSE)
		return (FALSE);
	if (env->input.num_of_times_eat != env->philo[i].num_of_times_ate)
	{
		if (philo_sleep(env, i) == FALSE)
			return (FALSE);
		if (philo_think(env, i) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

void	*routine(void *args)
{
	t_env	*env;
	int		i;

	env = (t_env *)args;
	i = env->n_thread;
	if (env->input.num_of_times_eat > 0)
	{
		while (env->input.num_of_times_eat > env->philo[i].num_of_times_ate
			&& env->philo_dead == FALSE)
			if (routine_execute(env, i) == FALSE)
				break ;
	}
	else
	{
		while (env->philo_dead == FALSE)
		{
			if (routine_execute(env, i) == FALSE)
				break ;
		}
	}
	return (NULL);
}

void	*anyone_die_yet(void *args)
{
	t_env	*env;
	int		i;

	env = (t_env *)args;
	i = 0;
	if (env->input.num_of_times_eat > 0)
	{
		while (env->input.num_of_times_eat > env->philo[i].num_of_times_ate
			&& env->philo_dead == FALSE)
			if (are_you_dead(env, &i) == TRUE)
				break ;
	}
	else
		while (env->philo_dead == FALSE)
			if (are_you_dead(env, &i) == TRUE)
				break ;
	return (NULL);
}

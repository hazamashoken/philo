/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:32:11 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/02 01:36:58 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_env(t_env *env)
{
	env->input.num_philo = 0;
	env->input.time_to_die = 0;
	env->input.time_to_eat = 0;
	env->input.time_to_sleep = 0;
	env->input.num_must_eat = -1;
	env->philo.eat_count = 0;
	env->philo.time_to_die = 0;
	env->philo.died = 0;
	env->philo_dead = 0;
	env->philo.id = 0;
	env->forks = SEM_FAILED;
	env->table = SEM_FAILED;
	env->print = SEM_FAILED;
}

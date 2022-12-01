/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:45:55 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/14 13:12:07 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

static void	set_philo(t_env *env, int i, int j)
{
	env->philo[i].id = i + 1;
	env->philo[i].num_of_times_ate = 0;
	env->philo[i].time_to_die = 0;
	env->philo[i].fork.left = i;
	env->philo[i].fork.right = j;
}

int	create_philos(t_env *env)
{
	int	i;
	int	j;

	env->philo = malloc(sizeof(t_env) * (env->input.num_philo + 1));
	if (env->philo == NULL)
		return (FALSE);
	i = 0;
	j = 1;
	while (j < env->input.num_philo)
		set_philo(env, i++, j++);
	set_philo(env, i, 0);
	return (TRUE);
}

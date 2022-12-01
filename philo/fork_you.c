/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_you.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:44:34 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 15:28:51 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

int	create_forks(t_env *env)
{
	int	i;

	env->forks = malloc(sizeof(pthread_mutex_t) * env->input.num_philo + 1);
	if (env->forks == NULL)
		return (FALSE);
	i = 0;
	while (i < env->input.num_philo)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_mutex_init(&env->table, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

void	unlock_forks(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->input.num_philo)
	{
		pthread_mutex_unlock(&env->forks[i]);
		i++;
	}
}

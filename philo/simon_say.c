/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simon_say.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:49:16 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/16 10:54:48 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print(t_env *env, int id, char *status, char *color)
{
	long long	now;

	now = delta_time(env->t0) / 1000;
	if (env->philo_dead == TRUE)
		return (FALSE);
	pthread_mutex_lock(&env->write);
	if (env->philo_dead == TRUE)
	{
		pthread_mutex_unlock(&env->write);
		return (FALSE);
	}
	else
		printf("%s%lld%-8s %d %-30s%s\n", color, now, " ms", id, status, RESET);
	pthread_mutex_unlock(&env->write);
	return (TRUE);
}

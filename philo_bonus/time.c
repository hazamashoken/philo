/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:32:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/09 21:59:14 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	delta_time(long long time)
{
	return (get_time() - time);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	my_sleep(t_env *env, int time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (env->philo_dead)
			return (EXIT_FAILURE);
		sem_wait(env->print);
		sem_post(env->print);
		usleep(200);
	}
	return (EXIT_SUCCESS);
}

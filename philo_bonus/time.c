/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:32:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/02 00:49:24 by tliangso         ###   ########.fr       */
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
		if (delta_time(env->philo.time_to_die) > env->input.time_to_die)
			env->philo_dead = 1;
		usleep(200);
	}
	return (EXIT_SUCCESS);
}

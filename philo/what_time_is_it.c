/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_time_is_it.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:37:53 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/09 16:04:51 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	delta_time(long long time)
{
	return (get_time() - time);
}

void	drop_all_forks(t_env *env)
{
	int	i;

	i = 1;
	while (i <= env->input.num_philo)
		drop_forks(env, i++);
}

void	my_usleep(long long time, t_env *env, int i)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (env->philo_dead)
		{
			destory_threads(env);
			drop_forks(env, i);
			pthread_mutex_unlock(&env->table);
			break ;
		}
		usleep(100);
	}
}

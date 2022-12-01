/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_time_is_it.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:37:53 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 15:15:39 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

long long	delta_time(long long time)
{
	struct timeval	tv;
	long long		delta;

	gettimeofday(&tv, NULL);
	delta = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (delta - time);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	exec_action(long long time)
{
	my_usleep(time);
}

void	my_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		usleep(200);
	}
}

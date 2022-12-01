/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_time_is_it.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:37:53 by tliangso          #+#    #+#             */
/*   Updated: 2022/11/11 13:29:05 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	exec_action(long long time)
{
	my_usleep(time * 1000);
}

void	my_usleep(long long time)
{
	struct timeval	tval;
	long long		cur_time;

	gettimeofday(&tval, NULL);
	cur_time = (tval.tv_sec * 1000000) + tval.tv_usec;
	usleep(time * 0.80);
	while ((tval.tv_sec * 1000000 + tval.tv_usec) - cur_time <= time)
	{
		gettimeofday(&tval, NULL);
		usleep(1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:41:14 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/15 17:42:09 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

typedef struct timeval t_time;
typedef unsigned long t_ms;

t_ms	diff_time(t_time t1, t_time t2)
{
	t_ms	ms1;
	t_ms	ms2;
	t_ms	delta;

	ms1 = (t1.tv_sec * 1000) + (t1.tv_usec / 1000);
	ms2 = (t2.tv_sec * 1000) + (t2.tv_usec / 1000);
	delta = ms1 - ms2;
	return (delta);
}

t_ms	delay_time(int delay)
{
	t_time	before;
	t_time	after;
	t_ms	delta;

	gettimeofday(&before, NULL);
	usleep(delay * 1000);
	gettimeofday(&after, NULL);
	delta = diff_time(after, before);
	return (delta - delay);
}

int	main(void)
{
	t_ms	delta;
	int		i;
	double	avg;
	int		round;

	i = -1;
	avg = 0;
	round = 100;
	while (++i < round)
	{
		delta = delay_time(100);
		avg += delta;
		printf("Sysdelay: %lu ms\n", delta);
	}
	printf("\navg delay for %d round: %.2fms\n",
		round, (float)avg / (float)round);
}

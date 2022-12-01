/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:43:51 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/15 18:30:08 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	*routine()
{
	int	i;
	int	j;

	i = -1;
	while (++i < 20)
	{
		j = -1;
		if (i != 1)
			printf("\n");
		while (++j < i)
			printf("+");
		usleep(100);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	pthread_create(&thread1, NULL, &routine, NULL);
	pthread_create(&thread2, NULL, &routine, NULL);
	pthread_create(&thread3, NULL, &routine, NULL);
	pthread_create(&thread4, NULL, &routine, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
}

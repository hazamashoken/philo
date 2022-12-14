/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:36:15 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 23:08:55 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	exit_failure(t_env *env)
{
	if (env->forks != SEM_FAILED)
		sem_close(env->forks);
	if (env->table != SEM_FAILED)
		sem_close(env->table);
	if (env->pid != NULL)
		free(env->pid);
	printf("%s%s%s", YELLOW, HELP, RESET);
	return (EXIT_FAILURE);
}

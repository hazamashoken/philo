/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:31:00 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 14:31:26 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_input(t_env *env)
{
	if (env->input.num_philo < 2 || env->input.num_philo > 200)
		return (EXIT_FAILURE);
	env->pid = (pid_t *)malloc(sizeof(pid_t) * env->input.num_philo);
	if (env->pid == NULL)
		return (EXIT_FAILURE);
	if (env->input.time_to_die < 60)
		return (EXIT_FAILURE);
	if (env->input.time_to_eat < 60)
		return (EXIT_FAILURE);
	if (env->input.time_to_sleep < 60)
		return (EXIT_FAILURE);
	if (env->input.num_must_eat < 0 && env->input.num_must_eat != -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_input(t_env *env, int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	i = argc;
	while (i > 1)
	{
		if (ft_checkset(argv[i - 1], "0123456789") == 0)
			return (EXIT_FAILURE);
		i--;
	}
	env->input.num_philo = ft_atoi(argv[1]);
	env->input.time_to_die = ft_atoi(argv[2]);
	env->input.time_to_eat = ft_atoi(argv[3]);
	env->input.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->input.num_must_eat = ft_atoi(argv[5]);
	return (check_input(env));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:33:01 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/09 22:25:35 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	args_errors(int argc, t_env *env)
{
	if (!env->input.num_philo)
		printf("%s%s%s\n", PINK,
			"Error: Invalid number of philo (1-200)\n", RESET);
	if (!env->input.time_to_die)
		printf("%s%s%s\n", PINK, "Error: Invalid time to die (60<=)\n", RESET);
	if (!env->input.time_to_eat)
		printf("%s%s%s\n", PINK, "Error: Invalid time to eat (60<=)\n", RESET);
	if (!env->input.time_to_sleep)
		printf("%s%s%s\n", PINK, "Error: Invalid time to sleep (60<=)\n", RESET);
	if (argc == 6 && !env->input.num_of_times_eat)
		printf("%s%s%s\n", PINK,
			"Error: Invalid number of time to eat (1<=)\n", RESET);
}

static int	check_input(t_env *env)
{
	if (env->input.num_philo < 2 || env->input.num_philo > 200)
		return (FALSE);
	if (env->input.time_to_die < 60)
		return (FALSE);
	if (env->input.time_to_eat < 60)
		return (FALSE);
	if (env->input.time_to_sleep < 60)
		return (FALSE);
	if (env->input.num_of_times_eat < 0 && env->input.num_of_times_eat != -1)
		return (FALSE);
	return (TRUE);
}

static int	init_env(int argc, char **argv, t_env *env)
{
	if (argc == 5 || argc == 6)
	{
		env->input.num_philo = ft_atoi(argv[1]);
		env->input.time_to_die = ft_atoi(argv[2]);
		env->input.time_to_eat = ft_atoi(argv[3]);
		env->input.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			env->input.num_of_times_eat = ft_atoi(argv[5]);
		else
			env->input.num_of_times_eat = -1;
		return (TRUE);
	}
	return (check_input(env));
}

int	check_args(int argc, char **argv, t_env *env)
{
	if (init_env(argc, argv, env) == FALSE)
	{
		printf("%s%s%s", YELLOW, HELP, RESET);
		return (FALSE);
	}
	else
	{
		args_errors(argc, env);
		if (!env->input.num_philo || !env->input.time_to_die
			|| !env->input.time_to_eat || !env->input.time_to_sleep
			|| (argc == 6 && !env->input.num_of_times_eat))
		{
			printf("%s%s%s", YELLOW, HELP, RESET);
			return (FALSE);
		}
	}
	return (TRUE);
}

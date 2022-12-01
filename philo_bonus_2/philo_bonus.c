/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:07:45 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 14:25:47 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "philo_define.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void	sem_unlink_all(void)
{
	sem_unlink("/forks");
	sem_unlink("/table");
}

int	sem_failure(t_env *env)
{
	if (env->forks != SEM_FAILED)
		sem_close(env->forks);
	if (env->table != SEM_FAILED)
		sem_close(env->table);
	return (EXIT_FAILURE);
}

int	create_semaphores(t_env *env)
{
	sem_unlink_all();
	env->forks = sem_open("/forks", O_CREAT, 0644, env->input.num_philo);
	env->table = sem_open("/table", O_CREAT, 0644, 1);
	if (env->forks == SEM_FAILED || env->table == SEM_FAILED)
		return (sem_failure(env));
	return (EXIT_SUCCESS);
}

int	check_input(t_env *env)
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

void	init_env(t_env *env)
{
	env->input.num_philo = 0;
	env->input.time_to_die = 0;
	env->input.time_to_eat = 0;
	env->input.time_to_sleep = 0;
	env->input.num_must_eat = -1;
	env->philo.eat_count = 0;
	env->philo.time_to_die = 0;
	env->philo.died = 0;
	env->philo_dead = 0;
	env->philo.id = 0;
	env->forks = SEM_FAILED;
	env->table = SEM_FAILED;
}

long long delta_time(long long time)
{
	struct timeval	tv;
	long long		delta;

	gettimeofday(&tv, NULL);
	delta = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	// printf("%lld %lld\n", time, delta);
	return (delta - time);
}

long long get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	my_sleep(t_env *env, int time)
{
	long long	start;

	(void)env;
	start = get_time();
	while (get_time() - start < time)
	{
		// printf("%lld\n",delta_time(env->philo.time_to_die));
		if (delta_time(env->philo.time_to_die) > env->input.time_to_die)
			env->philo_dead = 1;
		usleep(200);
	}
	return (EXIT_SUCCESS);
}

void	*monitor(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (env->philo.eat_count <= env->input.num_must_eat
		|| env->input.num_must_eat == -1)
	{
		if (env->philo_dead)
		{
			sem_wait(env->table);
			printf("%s%lld %d died%s\n", RED, delta_time(env->t0), env->philo.id, RESET);
			exit(PHILO_DIED);
		}
	}
	printf("done\n");
	return (NULL);
}

void	routine(t_env *env)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &monitor, env);
	pthread_detach(thread);
	while (env->philo.eat_count < env->input.num_must_eat
		|| env->input.num_must_eat == -1)
	{
		sem_wait(env->table);
		sem_wait(env->forks);
		printf("%s%lld %d has taken a fork%s\n", YELLOW, delta_time(env->t0), env->philo.id, RESET);
		sem_wait(env->forks);
		printf("%s%lld %d has taken a fork%s\n", YELLOW, delta_time(env->t0), env->philo.id, RESET);
		sem_post(env->table);
		printf("%s%lld %d is eating%s\n", GREEN, delta_time(env->t0), env->philo.id, RESET);
		my_sleep(env, env->input.time_to_eat);
		env->philo.eat_count++;
		env->philo.time_to_die = get_time();
		sem_post(env->forks);
		sem_post(env->forks);
		printf("%s%lld %d is sleeping%s\n", PINK, delta_time(env->t0), env->philo.id, RESET);
		my_sleep(env, env->input.time_to_sleep);
		printf("%s%lld %d is thinking%s\n", BLUE, delta_time(env->t0), env->philo.id, RESET);
	}
	exit(PHILO_DONE);
}

int	create_process(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->input.num_philo)
	{
		env->n_process = i;
		env->philo.id++;
		env->philo.time_to_die = get_time();
		env->pid[i] = fork();
		if (env->pid[i] == -1)
			return (EXIT_FAILURE);
		if (env->pid[i] == 0)
		{
			routine(env);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	destroy_free_env(t_env *env)
{
	int	i;
	int	status;

	i = 0;
	while (i < env->input.num_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == PHILO_DIED)
		{
			while (i < env->input.num_philo)
				kill(env->pid[i++], SIGKILL);
			break ;
		}
		i++;
	}
	if (env->forks != SEM_FAILED)
		sem_close(env->forks);
	if (env->table != SEM_FAILED)
		sem_close(env->table);
	if (env->pid != NULL)
		free(env->pid);
}

int	exit_failure(t_env *env)
{
	if (env->forks != SEM_FAILED)
		sem_close(env->forks);
	if (env->table != SEM_FAILED)
		sem_close(env->table);
	if (env->pid != NULL)
		free(env->pid);
	printf("error\n");
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_env	env;

	init_env(&env);
	if (parse_input(&env, argc, argv) == EXIT_FAILURE)
		return (exit_failure(&env));
	if (create_semaphores(&env) == EXIT_FAILURE)
		return (exit_failure(&env));
	env.t0 = get_time();
	if (create_process(&env) == EXIT_FAILURE)
		return (exit_failure(&env));
	destroy_free_env(&env);
	return (EXIT_SUCCESS);
}

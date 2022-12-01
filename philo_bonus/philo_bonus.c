/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:08:16 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/01 11:51:50 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo_bonus.h"

int	sem_unlink_all(void)
{
	if (sem_unlink("/forks") == -1)
		return (EXIT_FAILURE);
	if (sem_unlink("/write") == -1)
		return (EXIT_FAILURE);
	if (sem_unlink("/dead") == -1)
		return (EXIT_FAILURE);
	if (sem_unlink("/eat") == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	sem_failure(t_env *env)
{
	if (env->forks != SEM_FAILED)
		sem_close(env->forks);
	if (env->write != SEM_FAILED)
		sem_close(env->write);
	if (env->dead != SEM_FAILED)
		sem_close(env->dead);
	if (env->eat != SEM_FAILED)
		sem_close(env->eat);
	return (EXIT_FAILURE);
}

int	create_semaphone(t_env *env)
{
	if (sem_unlink_all())
		return (EXIT_FAILURE);
	env->forks = sem_open("/forks", O_CREAT, 0644, env->input.num_philo);
	env->write = sem_open("/write", O_CREAT, 0644, 1);
	env->dead = sem_open("/dead", O_CREAT, 0644, 0);
	env->eat = sem_open("/eat", O_CREAT, 0644, 1);
	if (env->forks == SEM_FAILED || env->write == SEM_FAILED
		|| env->dead == SEM_FAILED || env->eat == SEM_FAILED)
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
	if (env->input.num_must_eat < 1 && env->input.num_must_eat != -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_input(t_env *env, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
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
	env->philo.alive = 0;
	env->philo.id = 0;
	env->forks = SEM_FAILED;
	env->write = SEM_FAILED;
	env->dead = SEM_FAILED;
	env->eat = SEM_FAILED;
}

void	*checker(void *arg)
{
	t_env		*env;
	long long	now;

	env = (t_env *)arg;
	env->philo.time_to_die = get_time();
	while (env->input.num_must_eat >= env->philo.eat_count
		|| env->input.num_must_eat == -1)
	{
		now = delta_time(env->philo.time_to_die);
		//printf("%lld %lld\n", now, env->philo.time_to_die);
		if (now > env->input.time_to_die)
		{
			sem_wait(env->write);
			sem_post(env->dead);
			printf("%s%lld%-8s %d %-30s%s\n", RED, now, " ms",
				env->philo.id, DIED, RESET);
			return (NULL);
		}
	}
	return (NULL);
}

int	philo_print(t_env *env, char *action, char *color)
{
	long long	now;

	now = delta_time(env->t0) / 1000;
	if (sem_wait(env->write) == -1)
		return (EXIT_FAILURE);
	printf("%s%lld%-8s %d %-30s%s\n", color, now, " ms",
		env->philo.id, action, RESET);
	if (sem_post(env->write) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	drop_forks(t_env *env)
{
	if (sem_post(env->forks) == -1)
		return (EXIT_FAILURE);
	if (sem_post(env->forks) == -1)
		return (EXIT_FAILURE);
	env->philo.eat_count++;
	return (EXIT_SUCCESS);
}

int	philo_eat(t_env *env)
{
	if (sem_wait(env->forks) == -1)
		return (EXIT_FAILURE);
	if (philo_print(env, LEFT_FORK, BLUE))
		return (EXIT_FAILURE);
	if (sem_wait(env->forks))
		return (EXIT_FAILURE);
	if (philo_print(env, RIGHT_FORK, BLUE))
		return (EXIT_FAILURE);
	if (philo_print(env, EAT, YELLOW))
		return (EXIT_FAILURE);
	env->philo.time_to_die = get_time();
	exec_action(env->input.time_to_eat);
	if (drop_forks(env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_think(t_env *env)
{
	if (philo_print(env, THINK, GREEN))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_sleep(t_env *env)
{
	printf("trying sleep\n");
	if (philo_print(env, SLEEP, GREEN))
		return (EXIT_FAILURE);
	printf("sleep\n");
	exec_action(env->input.time_to_sleep);
	printf("wake\n");
	return (EXIT_SUCCESS);
}

int	routine_execute(t_env *env)
{
	if (philo_eat(env))
		return (EXIT_FAILURE);
	printf("%d %d\n",env->input.num_must_eat, env->philo.eat_count);
	if (env->input.num_must_eat >= env->philo.eat_count
		|| env->input.num_must_eat == -1)
	{
		if (philo_sleep(env))
			return (EXIT_FAILURE);
		if (philo_think(env))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*philo_routine(t_env *env)
{
	pthread_create(&env->checker, NULL,
		checker, env);
	pthread_detach(env->checker);
	while (env->input.num_must_eat == -1
		|| env->philo.eat_count < env->input.num_must_eat)
	{
		if (routine_execute(env))
			return (NULL);
	}
	return (NULL);
}

int	create_process(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->input.num_philo)
	{
		env->philo.id = i + 1;
		env->t0 = get_time();
		env->pid[i] = fork();
		if (env->pid[i] == 0)
		{
			philo_routine(env);
			exit(EXIT_SUCCESS);
		}
		else if (env->pid[i] < 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	*philo_waiter(void *arg)
{
	int		i;
	t_env	*env;

	i = 0;
	env = (t_env *)arg;
	while (i < env->input.num_philo)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	sem_post(env->dead);
	return (NULL);
}

void	*philo_killer(void *arg)
{
	int		i;
	t_env	*env;

	i = 0;
	env = (t_env *)arg;
	sem_wait(env->dead);
	while (i < env->input.num_philo)
	{
		kill(env->pid[i], SIGTERM);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_env		env;
	pthread_t	thread;

	init_env(&env);
	if (parse_input(&env, argc, argv))
		return (EXIT_FAILURE);
	if (create_semaphone(&env))
		return (EXIT_FAILURE);
	if (create_process(&env))
		return (EXIT_FAILURE);
	if (env.input.num_must_eat != -1)
		pthread_create(&thread, NULL, philo_waiter, &env);
	pthread_create(&thread, NULL, philo_killer, &env);
	pthread_join(thread, NULL);
	free(env.pid);
	sem_failure(&env);
	return (EXIT_SUCCESS);
}

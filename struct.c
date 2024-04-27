/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcelo <marcelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:31:25 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/28 00:44:35 by marcelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_program *prog)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * prog->n_philos);
	if (!forks)
		return (0);
	prog->forks = forks;
	i = 0;
	while (i < prog->n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (destroy_mutexes(prog, 0, i));
		i++;
	}
	if (pthread_mutex_init(&prog->end, NULL) != 0)
		return (destroy_mutexes(prog, 1, i - 1));
	if (pthread_mutex_init(&prog->print, NULL) != 0)
		return (destroy_mutexes(prog, 2, i - 1));
	if (pthread_mutex_init(&prog->monitor, NULL) != 0)
		return (destroy_mutexes(prog, 3, i - 1));
	return (1);
}

int	init_philos(t_program *prog)
{
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(t_philo) * prog->n_philos);
	if (!philo)
		return (0);
	prog->philos = philo;
	i = 0;
	while (i < prog->n_philos)
	{
		philo[i].prog = prog;
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].meals = 0;
		philo[i].l_fork = &prog->forks[i];
		if (i == prog->n_philos - 1)
			philo[i].r_fork = &prog->forks[0];
		else
			philo[i].r_fork = &prog->forks[i + 1];
		i++;
	}
	return (1);
}

int	init_program(char **argv, t_program *prog)
{
	prog->n_philos = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->threads_ready = false;
	prog->is_dead = false;
	prog->is_full = false;
	prog->fail_thread_creation = false;
	prog->times_to_eat = 0;
	if (argv[5])
		prog->times_to_eat = ft_atoi(argv[5]);
	if (!init_mutexes(prog))
		return (0);
	if (!init_philos(prog))
		return (0);
	if (!create_join_threads(prog))
		return (0);
	return (1);
}

//funcao que retorna 0 e destroi as mutexes
int	destroy_mutexes(t_program *prog, int flag, int n)
{
	while (n >= 0)
		pthread_mutex_destroy(&prog->forks[n--]);
	if (flag == 1)
		pthread_mutex_destroy(&prog->end);
	else if (flag == 2)
	{
		pthread_mutex_destroy(&prog->end);
		pthread_mutex_destroy(&prog->print);
	}
	else if (flag == 3)
	{
		pthread_mutex_destroy(&prog->end);
		pthread_mutex_destroy(&prog->print);
		pthread_mutex_destroy(&prog->monitor);
	}
	return (0);
}

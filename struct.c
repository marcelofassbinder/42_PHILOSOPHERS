/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:31:25 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/22 19:31:04 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int init_mutexes(t_program *prog)
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
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&prog->death, NULL);
	pthread_mutex_init(&prog->print, NULL);
	pthread_mutex_init(&prog->monitor, NULL);
	return (1);
}
 
int init_philos(t_program *prog)
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
		philo[i].l_fork = &prog->forks[i];
		if (i == prog->n_philos - 1)
			philo[i].r_fork = &prog->forks[0];
		else
			philo[i].r_fork = &prog->forks[i + 1];
		i++;
	}
	return(1);
}

int	init_program(char **argv, t_program *prog)
{
	prog->n_philos = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->threads_ready = false;
	prog->is_dead = false;
	prog->times_must_eat = 0;
	if (argv[5])
		prog->times_must_eat = ft_atoi(argv[5]);
	if (!init_mutexes(prog))
		return (0);
	if (!init_philos(prog))
		return (0);
	if (!create_join_threads(prog))
		return (0);
	return (1);
}

int	create_join_threads(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_philos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL, &routine, &prog->philos[i]) != 0)
			return (0);
		i++;
	}
	prog->start = get_current_time();
	pthread_mutex_lock(&prog->monitor);
	prog->threads_ready = true;
	pthread_mutex_unlock(&prog->monitor);
	monitoring(prog);
	i = 0;
	while (i < prog->n_philos)
	{
		if (pthread_join(prog->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	wait_threads_creation(t_program *prog)
{
	while (1)
	{
		pthread_mutex_lock(&prog->monitor);
		if (prog->threads_ready == true)
		{
			pthread_mutex_unlock(&prog->monitor);
			break;
		}
		pthread_mutex_unlock(&prog->monitor);
	}
}

void	free_philos_and_forks(t_program *prog)
{
	int i;

	i = 0;
	while (i < prog->n_philos)
	{
		free(&prog->forks[i]);
		free(&prog->philos[i]);
		i++;
	}
}

void	destroy_mutexes(t_program *prog)
{
	int i;

	i = 0;
	while (i < prog->n_philos)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prog->print);
	pthread_mutex_destroy(&prog->monitor);
	pthread_mutex_destroy(&prog->death);
}
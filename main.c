/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/18 19:40:18 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo 	ph;

	ph = *(t_philo *)philo;
	//pthread_mutex_lock(ph.fork);
	printf("ola eu sou o philo %i\n", ph.id);
	//pthread_mutex_unlock(ph.fork);
	return (NULL);
}
 
int init_philos(t_program *prog)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	int				i;
	
	philo = malloc(sizeof(t_philo) * prog->n_philos);
	if (!philo)
		return (0);
	fork = malloc(sizeof(t_philo) * prog->n_philos);
	if (!fork)
		return (0);
	i = 0;
	while (i < prog->n_philos)
	{
		philo[i].prog = prog;
		philo[i].id = i + 1;
		philo[i].fork = &fork[i];
		pthread_mutex_init(philo[i].fork, NULL);
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	prog->philos = philo;
	prog->forks = fork;
	return(1);
}

void	define_next_fork(t_program *prog)
{
	int	i;

	i = 0;
	while(i < prog->n_philos - 1)
	{
		prog->philos[i].next_fork = prog->philos[i + 1].fork;
		i++;
	}
	prog->philos[i].next_fork = prog->philos[0].fork;
}

int	init_program(char **argv, t_program *prog)
{
	int			i;
	
	prog->n_philos = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		prog->times_must_eat = ft_atoi(argv[5]);
	if (!init_philos(prog))
		return (0);
	define_next_fork(prog);
	i = 0;
	while (i < prog->n_philos)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	prog;
	
	if (!check_input(argc, argv))
		return (1);
	init_program(argv, &prog);
}

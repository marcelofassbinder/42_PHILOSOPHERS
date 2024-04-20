/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:31:25 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/20 19:54:28 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int init_forks(t_program *prog)
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
	if (!init_forks(prog))
		return (0);
	i = 0;
	while (i < prog->n_philos)
	{
		philo[i].prog = prog;
		philo[i].id = i + 1;
		philo[i].is_dead = 0;
		philo[i].l_fork = &prog->forks[i];
		if (i == prog->n_philos - 1)
			philo[i].r_fork = &prog->forks[0];
		else
			philo[i].r_fork = &prog->forks[i + 1];
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	prog->threads_ready = true;
	return(1);
}
//funcao deve monitorar as threads, esperando todas serem criadas para comecar a monitorar

int monitoring(t_program *prog)
{
	int	i;
	
	while (1)
	{
		if (prog->threads_ready == true)
		{
			i = 0;
			while (1)
			{
				if ((get_current_time() - prog->start) - prog->philos[i].last_meal > (unsigned long)prog->time_to_die)
				{
					printf("the philo died\n");
					exit (0);
				}
				i++;
			}
		}
	}
}

int	init_program(char **argv, t_program *prog)
{
	//pthread_t	*monitor;
	int			i;
	
	prog->start = get_current_time();
	prog->n_philos = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->times_must_eat = 0;
	prog->threads_ready = false;
	if (argv[5])
		prog->times_must_eat = ft_atoi(argv[5]);
	if (!init_philos(prog))
		return (0);
	i = 0;
	while (i < prog->n_philos)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
	return (1);
}
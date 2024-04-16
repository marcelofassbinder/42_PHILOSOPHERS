/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/16 19:12:33 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo 	ph;

	ph = *(t_philo *)philo;
	pthread_mutex_init(&ph.fork, NULL);
	pthread_mutex_lock(&ph.fork);
	printf("ola eu sou o philo %i\n", ph.id);
	pthread_mutex_unlock(&ph.fork);
	return (NULL);
}

t_philo	init_philo(int i)
{
	t_philo			philo;
	pthread_mutex_t	fork;

	philo.id = i + 1;
	philo.fork = &fork;
	pthread_create(&philo.thread, NULL, &routine, &philo);
	return(philo);
}

t_program init_program(int n)
{
	t_program	prog;
	int			i;

	prog.philos = malloc(sizeof(t_philo) * n);
	i = 0;
	while (i < n)
	{
		prog.philos[i] = init_philo(i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		prog.philos->next_fork = 
		pthread_join(prog.philos[i].thread, NULL);
		i++;
	}
	return(prog);
}

int	main(int argc, char **argv)
{
	int			n;
	t_program	prog;
	
	if (!check_input(argc, argv))
		return (1);
	n = ft_atoi(argv[1]);
	prog = init_program(n);
}
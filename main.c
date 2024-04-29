/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/29 20:05:40 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief The entry point for the thread routine that will be executed by each philosopher.
 *
 * 1) The parameter "void *" is transformed to a "t_philo *";
 * 2) The function waits for all the threads to be created;
 * 3) Sleeps all the even philo id's, making the odd philos start eating first;
 * 4) Create a infinite loop, where the philo will eat, sleep and think, and
 * this loop will end only when a philo dies or all the philos eat
 * "times_to_eat" passed as parameter;
 * 
 * @param philo A pointer to the `philo` object representing a philosopher.
 * @return A void pointer to the exit status of the thread routine.
 */
void	*routine(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *)philo;
	if (!wait_threads_creation(ph->prog))
		return (NULL);
	if (ph->id % 2 == 0)
		ft_usleep(10);
	if (ph->prog->n_philos == 1)
		return (one_philo(ph));
	while (1)
	{
		if (check_dinner_end(ph) == 1)
			return (NULL);
		if (ph->id % 2 != 0)
			eating(ph, ph->l_fork, ph->r_fork);
		else if (ph->id % 2 == 0)
			eating(ph, ph->r_fork, ph->l_fork);
		sleeping(ph);
		thinking(ph);
	}
	return (NULL);
}

/**
 * Monitors the threads execution.
 *
 * Checks if a philosopher has died or if all the philosophers are full,
 * returning zero if either condition occurs.
 *
 * @param prog A pointer to a `t_program` structure representing the program.
 * @return An integer value indicating the status of the monitoring process.
 */
int	monitoring(t_program *prog)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < prog->n_philos)
		{
			pthread_mutex_lock(&prog->monitor);
			if (check_death(prog, i) == 1)
				return (0);
			if (check_meals(prog) == 1)
				return (0);
			pthread_mutex_unlock(&prog->monitor);
			i++;
		}
	}
	return (1);
}

void	*one_philo(t_philo *ph)
{
	pthread_mutex_lock(ph->l_fork);
	print_action(ph, "has taken a fork", BLUE);
	pthread_mutex_unlock(ph->l_fork);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_program	prog;

	if (!check_input(argc, argv))
		return (1);
	if (!init_program(argv, &prog))
		return (1);
	destroy_mutexes(&prog, 3, prog.n_philos - 1);
	free(prog.philos);
	free(prog.forks);
}

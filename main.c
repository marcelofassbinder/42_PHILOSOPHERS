/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/28 18:19:37 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (check_meals(prog, i) == 1)
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

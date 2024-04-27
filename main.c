/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/27 17:08:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo 	*ph;
	size_t		start;

	ph = (t_philo *)philo;
	if (!wait_threads_creation(ph->prog))
		return (NULL);
	start = ph->prog->start;
	if (ph->id % 2 == 0)
		ft_usleep(10);
	if (ph->prog->n_philos == 1)
		return(one_philo(ph));
	while(1)
	{
		if (check_dinner_end(ph) == 1)
			return (NULL);
		if (ph->id % 2 != 0)
			eating(ph, start, ph->l_fork, ph->r_fork);
		else if (ph->id % 2 == 0)
			eating(ph, start, ph->r_fork, ph->l_fork);
		sleeping(ph);
		thinking(ph);
	}
	return (NULL);
}

void	*one_philo(t_philo *ph)
{
	pthread_mutex_lock(ph->l_fork);
	print_action(ph, "has taken a fork", BLUE);
	pthread_mutex_unlock(ph->l_fork);
	return (NULL);
}

int	check_dinner_end(t_philo *ph)
{
	pthread_mutex_lock(&ph->prog->end);
	if (ph->prog->is_dead || ph->prog->is_full)
	{
		pthread_mutex_unlock(&ph->prog->end);
		return (1);
	}
	pthread_mutex_unlock(&ph->prog->end);
	return (0);
}	

int monitoring(t_program *prog)
{
	int i;
	
	while (1)
	{
		i = 0;
		while (i < prog->n_philos)
		{
			pthread_mutex_lock(&prog->monitor);
			if ((get_current_time() - prog->start) - prog->philos[i].last_meal >= (size_t)prog->time_to_die)
			{
				print_action(&prog->philos[i], "died", RED);
				pthread_mutex_lock(&prog->end);
				prog->is_dead = true;
				pthread_mutex_unlock(&prog->end);
				pthread_mutex_unlock(&prog->monitor);
				return(0);
			}
			if (prog->times_must_eat > 0 && prog->philos[i].meals > prog->times_must_eat)
			{
				pthread_mutex_lock(&prog->end);
				prog->is_full = true;
				pthread_mutex_unlock(&prog->end);
				pthread_mutex_unlock(&prog->monitor);
				return (0);
			}
			pthread_mutex_unlock(&prog->monitor);
			i++;
		}
	}
	return (1);
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

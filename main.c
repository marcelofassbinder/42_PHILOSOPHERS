/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/22 19:47:31 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo 	*ph;
	size_t		start;

	ph = (t_philo *)philo;
	wait_threads_creation(ph->prog);
	start = ph->prog->start;
	if (ph->id % 2 == 0)
		usleep(10000);
	while(1)
	{
		pthread_mutex_lock(&ph->prog->death);
		if (ph->prog->is_dead == true)
		{
			pthread_mutex_unlock(&ph->prog->death);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->prog->death);
		if (ph->id % 2 != 0)
			ph_is_eating(ph, start, ph->l_fork, ph->r_fork);
		else if (ph->id % 2 == 0)
			ph_is_eating(ph, start, ph->r_fork, ph->l_fork);
		print_action(ph, "is sleeping", MAGENTA);
		usleep(ph->prog->time_to_sleep * 1000);
		print_action(ph, "is thinking", YELLOW);
	}
	return (NULL);
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
					pthread_mutex_lock(&prog->death);
					prog->is_dead = true;
					pthread_mutex_unlock(&prog->death);
					pthread_mutex_unlock(&prog->monitor);
					return(0);
				}
			pthread_mutex_unlock(&prog->monitor);
			i++;
		}
	}
	return (1);
}

void	ph_is_eating(t_philo *ph, size_t start, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	print_action(ph, "has taken a fork", BLUE);
	pthread_mutex_lock(second_fork);
	print_action(ph, "has taken a fork", BLUE);
	print_action(ph, "is eating", GREEN);
	pthread_mutex_lock(&ph->prog->monitor);
	ph->last_meal = get_current_time() - start;
	pthread_mutex_unlock(&ph->prog->monitor);
	usleep(ph->prog->time_to_eat * 1000);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

int	main(int argc, char **argv)
{
	t_program	prog;
	
	if (!check_input(argc, argv))
		return (1);
	if (!init_program(argv, &prog))
		return (1);
	destroy_mutexes(&prog);
}

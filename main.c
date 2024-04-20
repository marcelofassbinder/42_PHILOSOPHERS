/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:32 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/20 19:54:27 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo 	ph;
	size_t		start;

	ph = *(t_philo *)philo;
	start = ph.prog->start;
	if (ph.id % 2 == 0)
		usleep(100);
	while(1)
	{
		if (ph.id % 2 != 0)
		{
			ph.last_meal = ph_is_eating(ph.id, start, ph.l_fork, ph.r_fork, ph.prog->time_to_eat);
		}
		else if (ph.id % 2 == 0)
		{
			ph.last_meal = ph_is_eating(ph.id, start, ph.r_fork, ph.l_fork, ph.prog->time_to_eat);
		}
		printf("\033[35m%zu philo %i is sleeping\033[0m\n", get_current_time() - start, ph.id);
		usleep(ph.prog->time_to_sleep * 1000);
		printf("%zu philo %i is thinking\n", get_current_time() - start, ph.id);
		/* if ((get_current_time() - start) - ph.last_meal > (unsigned long)ph.prog->time_to_die)
		{
			ph.is_dead = 1; 
			printf("current time - last meal = %zu\n", (get_current_time() - start) - ph.last_meal);
			printf("time to die = %d\n", ph.prog->time_to_die);
			printf("\033[31m%zu philo %i died\033[0m\n", get_current_time() - start, ph.id);
			exit(0); 
		}*/
	}
	return (NULL);
}

size_t	ph_is_eating(int id, size_t start, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork, int time_to_eat)
{
	size_t	last_meal;

	pthread_mutex_lock(first_fork);
	printf("\033[33m%zu philo %i has taken a fork\033[0m\n", get_current_time() - start, id);
	pthread_mutex_lock(second_fork);
	printf("\033[33m%zu philo %i has taken a fork\033[0m\n", get_current_time() - start, id);
	printf("\033[32m%zu philo %i is eating\033[0m\n", get_current_time() - start, id);
	last_meal = get_current_time() - start;
	usleep(time_to_eat * 1000);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (last_meal);
}

int	main(int argc, char **argv)
{
	t_program	prog;
	
	if (!check_input(argc, argv))
		return (1);
	init_program(argv, &prog);
	monitoring(&prog);
}

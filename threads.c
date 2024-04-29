/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:09:32 by marcelo           #+#    #+#             */
/*   Updated: 2024/04/29 20:10:57 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_join_threads(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_philos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL, &routine,
				&prog->philos[i]) != 0)
		{
			prog->fail_thread_creation = true;
			return (0);
		}
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
		if (pthread_join(prog->philos[i++].thread, NULL) != 0)
			return (0);
	}
	return (1);
}

int	wait_threads_creation(t_program *prog)
{
	while (1)
	{
		pthread_mutex_lock(&prog->monitor);
		if (prog->fail_thread_creation == true)
		{
			pthread_mutex_unlock(&prog->monitor);
			return (0);
		}
		if (prog->threads_ready == true)
		{
			pthread_mutex_unlock(&prog->monitor);
			break ;
		}
		pthread_mutex_unlock(&prog->monitor);
	}
	return (1);
}

/**
 * Checks if is necessary to finish the actual philo thread.
 * It happens if a philosopher has died or all the philos are full.
 *
 * @param ph A pointer to the philosopher.
 * @return Returns 1 if the thread must finish, 0 otherwise.
 */
int	check_dinner_end(t_philo *ph)
{
	pthread_mutex_lock(&ph->prog->end);
	if (ph->prog->is_dead || ph->prog->philos_are_full)
	{
		pthread_mutex_unlock(&ph->prog->end);
		return (1);
	}
	pthread_mutex_unlock(&ph->prog->end);
	return (0);
}

/**
 * Checks if a philosopher has died.
 *
 * This function is responsible for checking if a philosopher has died by
 * comparing the current time with the time of their last meal. If the
 * difference exceeds "time_to_die", the philosopher is considered
 * dead.
 *
 * @param prog The program structure containing the philosopher's information.
 * @param i The index of the philosopher.
 * @return 1 if the philosopher has died, 0 otherwise.
 */
int	check_death(t_program *prog, int i)
{
	if ((get_current_time() - prog->start) - prog->philos[i].last_meal
		>= (size_t)prog->time_to_die)
	{
		print_action(&prog->philos[i], "died", RED);
		pthread_mutex_lock(&prog->end);
		prog->is_dead = true;
		pthread_mutex_unlock(&prog->end);
		pthread_mutex_unlock(&prog->monitor);
		return (1);
	}
	return (0);
}

/**
 * Checks if the number of full philosophers is equal to the number of philosophers. If
 * this happens, the program needs to finish.
 *
 * @param prog A pointer to the philosopher program.
 * @return The number of meals eaten by the philosopher program.
 */
int	check_meals(t_program *prog)
{
	if (count_philos_full(prog) == prog->n_philos)
	{
		pthread_mutex_lock(&prog->end);
		prog->philos_are_full = true;
		pthread_mutex_unlock(&prog->end);
		pthread_mutex_unlock(&prog->monitor);
		return (1);
	}
	return (0);
}

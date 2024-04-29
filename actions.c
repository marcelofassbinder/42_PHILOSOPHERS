/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:50:36 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/29 19:34:04 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Prints an action performed by a philosopher, only if a philo is not dead or
 * if all the philos are not full, protecting it with a mutex. 
 *
 * @param philo  Pointer to the philosopher structure.
 * @param msg    The message to be printed.
 * @param color  The color of the message.
 */
void	print_action(t_philo *philo, char *msg, char *color)
{
	pthread_mutex_lock(&philo->prog->end);
	if (philo->prog->is_dead == false && philo->prog->philos_are_full == false)
	{
		pthread_mutex_lock(&philo->prog->print);
		printf("%s%zu %i %s%s\n", color, get_current_time()
			- philo->prog->start, philo->id, msg, RESET);
		pthread_mutex_unlock(&philo->prog->print);
	}
	pthread_mutex_unlock(&philo->prog->end);
}

/**
 * @brief Represents the action of a philosopher eating.
 *
 *	Lock first and second fork mutexes, then print the philo is eating,
 * store the actual time of start of the meal, then sleep the thread for
 * "time_to_eat" milisseconds, passed as parameter. Increase the philo meals
 * variable and check if the philo is full.
 *
 * @param ph Pointer to the philosopher struct.
 * @param first_fork Pointer to the first fork mutex.
 * @param second_fork Pointer to the second fork mutex.
 */
void	eating(t_philo *ph, pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	print_action(ph, "has taken a fork", BLUE);
	pthread_mutex_lock(second_fork);
	print_action(ph, "has taken a fork", BLUE);
	print_action(ph, "is eating", GREEN);
	pthread_mutex_lock(&ph->prog->monitor);
	ph->last_meal = get_current_time() - ph->prog->start;
	pthread_mutex_unlock(&ph->prog->monitor);
	ft_usleep(ph->prog->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_lock(&ph->prog->monitor);
	ph->meals++;
	if (ph->meals == ph->prog->times_to_eat)
		ph->is_full = true;
	pthread_mutex_unlock(&ph->prog->monitor);
}

/**
 * @brief Prints the actual philosopher is sleeping.
 * 
 * Sleep the thread "time_to_sleep" milisseconds, passed as parameter
 *
 * @param ph A pointer to a `t_philo` structure representing the philosopher.
 */
void	sleeping(t_philo *ph)
{
	print_action(ph, "is sleeping", MAGENTA);
	ft_usleep(ph->prog->time_to_sleep);
}

/**
 * @brief Prints the actual philosopher is thinking.
 * 
 * Sleep the thread 1 milissecond when the philo id is odd, to avoid philos of
 * eating 2 times when another still did not eat.
 *
 * @param ph A pointer to a `t_philo` structure representing the philosopher.
 */
void	thinking(t_philo *ph)
{
	print_action(ph, "is thinking", YELLOW);
	if (ph->prog->n_philos % 2 != 0)
		ft_usleep(1);
}

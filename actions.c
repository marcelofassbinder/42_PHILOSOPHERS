/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:50:36 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/28 18:22:27 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg, char *color)
{
	pthread_mutex_lock(&philo->prog->end);
	if (philo->prog->is_dead == false && philo->prog->is_full == false)
	{
		pthread_mutex_lock(&philo->prog->print);
		printf("%s%zu %i %s%s\n", color, get_current_time()
			- philo->prog->start, philo->id, msg, RESET);
		pthread_mutex_unlock(&philo->prog->print);
	}
	pthread_mutex_unlock(&philo->prog->end);
}

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
	pthread_mutex_unlock(&ph->prog->monitor);
}

void	sleeping(t_philo *ph)
{
	print_action(ph, "is sleeping", MAGENTA);
	ft_usleep(ph->prog->time_to_sleep);
}

void	thinking(t_philo *ph)
{
	print_action(ph, "is thinking", YELLOW);
	if (ph->prog->n_philos % 2 != 0)
		ft_usleep(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:09:32 by marcelo           #+#    #+#             */
/*   Updated: 2024/04/28 18:08:08 by mfassbin         ###   ########.fr       */
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
	pthread_mutex_lock(&prog->monitor);
	prog->threads_ready = true;
	pthread_mutex_unlock(&prog->monitor);
	prog->start = get_current_time();
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

int	check_meals(t_program *prog, int i)
{
	if (prog->times_to_eat > 0 && prog->philos[i].meals > prog->times_to_eat)
	{
		pthread_mutex_lock(&prog->end);
		prog->is_full = true;
		pthread_mutex_unlock(&prog->end);
		pthread_mutex_unlock(&prog->monitor);
		return (1);
	}
	return (0);
}

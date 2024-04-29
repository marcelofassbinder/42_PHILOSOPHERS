/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:13 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/29 20:10:57 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Converts a string to an integer.
 *
 * @param str The string to convert.
 * @return The converted integer value.
 */
int	ft_atoi(char *str)
{
	int	i;
	int	menos;
	int	nbr;

	nbr = 0;
	menos = 0;
	i = 0;
	while (str[i] != '\0' && ((str[i] <= 13 && str[i] >= 9) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			menos++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (menos == 0)
		return (nbr);
	return (-nbr);
}

/**
 * Retrieves the current time in milisseconds.
 *
 * @return The current time as a `size_t` value.
 */
size_t	get_current_time(void)
{
	struct timeval	t;
	size_t			current;

	gettimeofday(&t, NULL);
	current = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (current);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(500);
}

int	count_philos_full(t_program *prog)
{
	int	i;
	int	philos_full;

	i = 0;
	philos_full = 0;
	while (i < prog->n_philos)
	{
		if (prog->philos[i].is_full == true)
			philos_full++;
		i++;
	}
	return (philos_full);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:36:13 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/22 18:44:21 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_action(t_philo *philo, char *msg, char *color)
{
	pthread_mutex_lock(&philo->prog->death);
	if (philo->prog->is_dead == false)
	{
		pthread_mutex_lock(&philo->prog->print);
		printf("%s%zu philo %i %s%s\n", color, get_current_time() - philo->prog->start, philo->id, msg, RESET);
		pthread_mutex_unlock(&philo->prog->print);
	}
	pthread_mutex_unlock(&philo->prog->death);
}
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

size_t	get_current_time(void)
{
	struct timeval	t;
	size_t 			current;

	gettimeofday(&t, NULL);
	current = (t.tv_sec * 1000) + (t.tv_usec/1000);
	return(current);
}

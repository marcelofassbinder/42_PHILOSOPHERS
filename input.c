/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:37:30 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/22 16:59:35 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Error!\nInvalid number of arguments.\n", 37);
		return (0);
	}
	if (!arg_is_digit(argv[1]) || !arg_is_digit(argv[2])
		|| !arg_is_digit(argv[3]) || !arg_is_digit(argv[4])
			|| (argv[5] && !arg_is_digit(argv[5])))
	{
		write(2, "Error!\nOne or more parameters are not valid.\n", 46);
		return (0);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		write(2, "Error!\nThe number of philosophers is not valid.\n", 48);
		return (0);
	}
	return (1);
}

int	arg_is_digit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return(0);
		i++;
	}
	return (1);
}
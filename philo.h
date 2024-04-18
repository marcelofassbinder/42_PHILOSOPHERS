/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:26:16 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/18 18:40:58 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// * * * STRUCUTURE * * *

typedef struct 		s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*next_fork;
	struct s_program	*prog;
}					t_philo;

typedef struct		s_program
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_program;


int	ft_atoi(char *str);
int check_input(int argc, char **argv);
int	arg_is_digit(char *str);

#endif
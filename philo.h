/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:26:16 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/20 19:42:15 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

// * * * STRUCUTURE * * *

typedef struct 		s_philo
{
	int					id;
	int					is_dead;
	size_t				last_meal;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	struct s_program	*prog;
}					t_philo;

typedef struct		s_program
{
	size_t			start;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	bool			threads_ready;
}					t_program;


void	*routine(void *philo);
int monitoring(t_program *prog);
size_t	ph_is_eating(int id, size_t start, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork, int time_to_eat);
int init_forks(t_program *prog);
int init_philos(t_program *prog);
int	init_program(char **argv, t_program *prog);
int	ft_atoi(char *str);
int check_input(int argc, char **argv);
int	arg_is_digit(char *str);
size_t	get_current_time(void);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:26:16 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/29 16:00:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// * * * LIBRARIES * * * 

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

// * * * COLORS * * *

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

// * * * STRUCUTURES * * *

typedef struct s_philo
{
	int					id;
	int					meals;
	size_t				last_meal;
	bool				is_full;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	struct s_program	*prog;
}					t_philo;

typedef struct s_program
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	size_t			start;
	bool			is_dead;
	bool			philos_are_full;
	bool			threads_ready;
	bool			fail_thread_creation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	monitor;
	pthread_mutex_t	end;
	t_philo			*philos;
}					t_program;

// * * * ACTIONS.C * * * 

void	print_action(t_philo *philo, char *msg, char *color);
void	eating(t_philo *ph, pthread_mutex_t *first_fork,
			pthread_mutex_t *second_fork);
void	sleeping(t_philo *ph);
void	thinking(t_philo *ph);

// * * * INPUT.C * * * 

int		check_input(int argc, char **argv);
int		arg_is_digit(char *str);

// * * * STRUCT.C * * * 

int		init_mutexes(t_program *prog);
int		init_philos(t_program *prog);
int		init_program(char **argv, t_program *prog);
int		destroy_mutexes(t_program *prog, int flag, int n);

// * * * THREADS.C * * * 

int		create_join_threads(t_program *prog);
int		wait_threads_creation(t_program *prog);
int		check_dinner_end(t_philo *ph);
int		check_death(t_program *prog, int i);
int		check_meals(t_program *prog);

// * * * MAIN.C * * *

void	*routine(void *philo);
int		monitoring(t_program *prog);
void	*one_philo(t_philo *ph);

// * * * UTILS.C * * * 

int		ft_atoi(char *str);
size_t	get_current_time(void);
void	ft_usleep(size_t time);
int		count_philos_full(t_program *prog);

#endif
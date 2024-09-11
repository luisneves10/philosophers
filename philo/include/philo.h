/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:35:21 by luibarbo          #+#    #+#             */
/*   Updated: 2024/08/12 17:43:23 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				nb;
	int				meal_count;
	pthread_t		thread;
	long int		last_meal;
	struct s_data	*data;
	pthread_mutex_t	m_lock;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	long			nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_meals;
	long			time_start;
	t_philo			*philo;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_print;
	int				stop;
}	t_data;

/* ------------------------------------------------------- PHILOSOPHERS ----- */
int			data_init(t_data *data, char **argv);
void		create_threads(t_data *data);
int			start_philo(t_data *data);
void		*routine(void *philo);

/* --------------------------------------------------------------- STOP ----- */
int			stop_philo(t_philo *philo, int update_stop);
void		*dead_philo(void *phil);

/* -------------------------------------------------------------- UTILS ----- */
void		*print_error(char *s);
long		ft_atol(char *s);
void		clean_all(t_data *data);

long long	timestamp(void);
void		precise_usleep(int ms);
void		print_message(t_philo *philo, char *s);

#endif

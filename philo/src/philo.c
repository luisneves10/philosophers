/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:35:23 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/03 15:56:39 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_fork(t_philo *philo)
{
	if (philo->nb % 2 == 0)
		pthread_mutex_lock(&philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->m_print);
	print_message(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->m_print);
	if (philo->data->nb_philos == 1)
	{
		precise_usleep(philo->data->time_to_die * 2);
		return ;
	}
	if (philo->nb % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->data->m_print);
	print_message(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->m_print);
}

void	have_a_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_lock);
	philo->last_meal = timestamp();
	pthread_mutex_lock(&philo->data->m_print);
	print_message(philo, "is eating");
	pthread_mutex_unlock(&philo->data->m_print);
	precise_usleep(philo->data->time_to_eat);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->m_lock);
	pthread_mutex_unlock(&philo->l_fork);
	if (philo->data->nb_philos > 1)
		pthread_mutex_unlock(philo->r_fork);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	print_message(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->m_print);
	pthread_mutex_lock(&philo->m_lock);
	precise_usleep(philo->data->time_to_sleep);
	pthread_mutex_unlock(&philo->m_lock);
	pthread_mutex_lock(&philo->data->m_print);
	print_message(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->m_print);
}

void	*routine(void *phil)
{
	t_philo		*philo;
	pthread_t	death_thread;

	philo = (t_philo *)phil;
	pthread_create(&death_thread, NULL, dead_philo, philo);
	if (philo->nb % 2 == 0)
		precise_usleep(philo->data->time_to_eat / 2);
	while (!stop_philo(philo, 0))
	{
		pick_fork(philo);
		have_a_meal(philo);
		if (philo->meal_count >= philo->data->nb_meals)
			break ;
		sleep_philo(philo);
	}
	pthread_join(death_thread, NULL);
	return (NULL);
}

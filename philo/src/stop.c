/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:20:03 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:49 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_philo(t_philo *philo, int update_stop)
{
	pthread_mutex_lock(&philo->data->m_stop);
	if (update_stop)
		philo->data->stop = 1;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_stop);
	return (0);
}

void	*dead_philo(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	while (!stop_philo(philo, 0))
	{
		pthread_mutex_lock(&philo->m_lock);
		if (philo->meal_count >= philo->data->nb_meals)
		{
			pthread_mutex_unlock(&philo->m_lock);
			return (NULL);
		}
		if (timestamp() - philo->last_meal > philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->m_lock);
			pthread_mutex_lock(&philo->data->m_print);
			print_message(philo, "died");
			pthread_mutex_unlock(&philo->data->m_print);
			stop_philo(philo, 1);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->m_lock);
		usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:41:09 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/03 14:59:47 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		if (pthread_create(&data->philo[i].thread, NULL,
				&routine, &data->philo[i]) != 0)
			return ;
	i = -1;
	while (++i < data->nb_philos)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return ;
	return ;
}

int	start_philo(t_data *data)
{
	int	i;

	data->time_start = timestamp();
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	i = -1;
	while (++i < data->nb_philos)
	{
		data->philo[i].nb = i + 1;
		data->philo[i].meal_count = 0;
		data->philo[i].last_meal = timestamp();
		data->philo[i].r_fork = NULL;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].m_lock, NULL);
		pthread_mutex_init(&data->philo[i].l_fork, NULL);
		if (i == data->nb_philos - 1)
			data->philo[i].r_fork = &data->philo[0].l_fork;
		else
			data->philo[i].r_fork = &data->philo[i + 1].l_fork;
	}
	create_threads(data);
	return (0);
}

int	data_init(t_data *data, char **argv)
{
	data->stop = 0;
	data->nb_philos = ft_atol(argv[1]);
	if (data->nb_philos == 0)
		return (0);
	data->time_to_die = ft_atol(argv[2]);
	if (data->time_to_die == 0)
		return (0);
	data->time_to_eat = ft_atol(argv[3]);
	if (data->time_to_eat == 0)
		return (0);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_sleep == 0)
		return (0);
	if (argv[5])
		data->nb_meals = ft_atol(argv[5]);
	if (argv[5] && data->nb_meals == 0)
		return (0);
	if (!argv[5])
		data->nb_meals = INT_MAX;
	data->philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philo)
		return (0);
	return (1);
}

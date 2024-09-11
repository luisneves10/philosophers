/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:02:12 by luibarbo          #+#    #+#             */
/*   Updated: 2024/09/03 14:59:53 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*print_error(char *s)
{
	printf("Error: %s\n", s);
	return (0);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static char	*valid_arg(char *s)
{
	int		len;
	char	*number;

	len = 0;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '+')
		s++;
	else if (*s == '-')
		return (print_error("Only positive numbers are accepted"));
	if (!ft_isdigit(*s))
		return (print_error("One or more arguments are not valid numbers"));
	number = s;
	while (ft_isdigit(*s++))
		len++;
	if (len > 10)
		return (print_error("One or more values are too big"));
	return (number);
}

long	ft_atol(char *s)
{
	long	res;

	res = 0;
	s = valid_arg(s);
	if (!s)
		return (0);
	while (ft_isdigit(*s))
		res = res * 10 + (*s++ - '0');
	if (res > INT_MAX)
		return ((long)print_error("One or more values are too big"));
	if (res == 0)
		print_error("All arguments must be positive");
	return (res);
}

void	clean_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->philo[i].m_lock);
		pthread_mutex_destroy(&data->philo[i].l_fork);
	}
	free (data->philo);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_print);
}

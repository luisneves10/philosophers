/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:33:04 by luibarbo          #+#    #+#             */
/*   Updated: 2024/08/19 11:45:34 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		print_error("Invalid number of arguments!");
		return (1);
	}
	if (!data_init(&data, argv))
		return (2);
	start_philo(&data);
	clean_all(&data);
	return (0);
}

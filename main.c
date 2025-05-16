/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muharsla <muharsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:15:50 by muharsla          #+#    #+#             */
/*   Updated: 2025/05/09 12:57:22 by muharsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->philos);
	free(data->forks);
}

static void	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_loop,
			&data->philos[i]);
		i++;
	}
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_all(&data, argc, argv) != 0)
		return (1);
	start_threads(&data);
	check_stop(&data);
	join_threads(&data);
	clean(&data);
	return (0);
}

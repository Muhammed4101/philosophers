/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muharsla <muharsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:26:46 by muharsla          #+#    #+#             */
/*   Updated: 2025/05/09 12:47:23 by muharsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (err("Wrong number of arguments"));
	data->num_philos = atoi(argv[1]);
	data->die_time = atoi(argv[2]);
	data->eat_time = atoi(argv[3]);
	data->sleep_time = atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = atoi(argv[5]);
	if (data->num_philos <= 0 || data->die_time <= 0
		|| data->eat_time <= 0 || data->sleep_time <= 0
		|| (argc == 6 && data->must_eat <= 0))
		return (err("Invalid argument values"));
	if (argc == 6 && data->die_time < (data->eat_time + data->sleep_time))
		return (err("Time to die too short for must_eat"));
	data->stop = 0;
	data->start_time = get_time();
	return (0);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (err("Malloc failed for forks"));
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (err("Malloc failed for philos"));
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].eat_count = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_all(t_data *data, int argc, char **argv)
{
	if (check_args(data, argc, argv) != 0)
		return (1);
	if (init_mutexes(data) != 0)
		return (1);
	if (init_philos(data) != 0)
		return (1);
	return (0);
}

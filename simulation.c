/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muharsla <muharsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:31:06 by muharsla          #+#    #+#             */
/*   Updated: 2025/05/09 17:00:01 by muharsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_simulation_stopped(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->stop_mutex);
	result = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (result);
}

int	check_death(t_data *data)
{
	int	i;

	if (data->must_eat > 0)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (get_time() - data->philos[i].last_meal >= data->die_time)
		{
			print(&data->philos[i], "died");
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_eat_count(t_data *data)
{
	int	i;
	int	completed;

	if (data->must_eat <= 0)
		return (0);
	i = 0;
	completed = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].eat_count >= data->must_eat)
			completed++;
		i++;
	}
	if (completed == data->num_philos)
	{
		(&data->stop_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	return (0);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_simulation_stopped(philo->data))
	{
		eat(philo);
		if (is_simulation_stopped(philo->data))
			break ;
		sleep_philo(philo);
		if (is_simulation_stopped(philo->data))
			break ;
		think(philo);
	}
	return (NULL);
}

void	check_stop(t_data *data)
{
	while (!is_simulation_stopped(data))
	{
		if (check_eat_count(data))
			return ;
		if (check_death(data))
			return ;
	}
}

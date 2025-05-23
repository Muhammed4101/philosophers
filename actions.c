/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muharsla <muharsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:49:14 by muharsla          #+#    #+#             */
/*   Updated: 2025/05/17 05:27:32 by muharsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
		usleep(philo->data->die_time * 1000);
		return ;
	}
	take_forks(philo);
	if (!philo->data->stop)
	{
		print(philo, "is eating");
		usleep(philo->data->eat_time * 1000);
		philo->eat_count++;
		philo->last_meal = get_time();
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_philo(t_philo *philo)
{
	if (!philo->data->stop)
	{
		print(philo, "is sleeping");
		usleep(philo->data->sleep_time * 1000);
	}
}

void	think(t_philo *philo)
{
	if (!philo->data->stop)
		print(philo, "is thinking");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muharsla <muharsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:33:50 by muharsla          #+#    #+#             */
/*   Updated: 2025/05/09 17:00:01 by muharsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print(t_philo *philo, char *msg)
{
	(&philo->data->print_mutex);
	if (!philo->data->stop || (msg[0] == 'd' && msg[1] == 'i' && msg[2] == 'e'))
	{
		printf("%ld %d %s\n", get_time() - philo->data->start_time,
			philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	err(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

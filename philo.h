/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muharsla <muharsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:15:43 by muharsla          #+#    #+#             */
/*   Updated: 2025/05/09 12:44:50 by muharsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				eat_count;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			start_time;
	int				stop;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	t_philo			*philos;
}	t_data;

int		init_all(t_data *data, int argc, char **argv);
long	get_time(void);
void	print(t_philo *philo, char *msg);
int		err(char *msg);
void	*philo_loop(void *arg);
void	check_stop(t_data *data);
int		check_death(t_data *data);
int		check_eat_count(t_data *data);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);

#endif
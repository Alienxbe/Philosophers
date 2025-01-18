/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:12:49 by marykman          #+#    #+#             */
/*   Updated: 2025/01/18 01:22:31 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

static int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		if (pthread_mutex_init(&data->forks[i], NULL)
			|| pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL))
			return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->print_mutex, NULL)
		|| pthread_mutex_init(&data->dead_mutex, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		gettimeofday(&data->philos[i].last_meal, NULL);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks
		[(i + 1) % data->philo_count];
		data->philos[i].data = data;
	}
}

static int	init_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		if (pthread_create(&data->philos[i].t,
				NULL, &routine, &data->philos[i]))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	join_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(data->philos[i].t, NULL))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_count);
	if (!data->philos || !data->forks)
		return (EXIT_FAILURE);
	if (init_mutex(data))
		return (EXIT_FAILURE);
	init_philo(data);
	gettimeofday(&data->start_time, NULL);
	if (init_thread(data))
		return (EXIT_FAILURE);
	monitoring(data);
	if (join_thread(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

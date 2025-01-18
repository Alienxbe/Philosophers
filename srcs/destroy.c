/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 01:08:22 by marykman          #+#    #+#             */
/*   Updated: 2025/01/18 01:22:04 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

static void	destroy_philo(t_data *data)
{
	int	i;

	if (!data->philos)
		return ;
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
	free(data->philos);
}

static void	destroy_forks(t_data *data)
{
	int	i;

	if (!data->forks)
		return ;
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
}

void	destroy_data(t_data *data)
{
	destroy_philo(data);
	destroy_forks(data);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
}

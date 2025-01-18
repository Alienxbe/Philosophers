/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 00:38:59 by marykman          #+#    #+#             */
/*   Updated: 2025/01/18 01:05:14 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

static void	check_death(t_philo *philo)
{
	unsigned long	last_meal_time;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal_time = get_time(philo->last_meal);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (last_meal_time < (unsigned long)philo->data->time_to_die)
		return ;
	pprint_state(philo, STATE_DEAD);
}

void	monitoring(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->dead_mutex);
	while (!data->dead)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		i = -1;
		while (++i < data->philo_count)
			check_death(&data->philos[i]);
		pthread_mutex_lock(&data->dead_mutex);
	}
	pthread_mutex_unlock(&data->dead_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:27:36 by marykman          #+#    #+#             */
/*   Updated: 2025/01/13 19:03:18 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(philo->data->time_to_eat / 2 * 1000);
	while (!philo->data->dead && (philo->data->max_eat == -1 || philo->eat_count < philo->data->max_eat))
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);

		// eating
		pprint_state(philo, STATE_EATING);
		gettimeofday(&philo->last_meal, NULL);
		usleep(philo->data->time_to_eat * 1000);

		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo->eat_count++;

		// sleeping
		pprint_state(philo, STATE_SLEEPING);
		usleep(philo->data->time_to_sleep * 1000);
		if (get_time(philo->last_meal) >= (unsigned long)philo->data->time_to_die)
		{
			pprint_state(philo, STATE_DEAD);
			pthread_mutex_lock(&philo->data->dead_mutex);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->dead_mutex);
			break ;
		}

		// thinking
		pprint_state(philo, STATE_THINKING);
		
	}
	return (NULL);
}
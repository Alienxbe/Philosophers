/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:27:36 by marykman          #+#    #+#             */
/*   Updated: 2025/01/18 01:05:10 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pprint_state(philo, STATE_FORK_TAKEN);
	pthread_mutex_lock(philo->right_fork);
	pprint_state(philo, STATE_FORK_TAKEN);
	pprint_state(philo, STATE_EATING);
	pthread_mutex_lock(&philo->last_meal_mutex);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->eat_count++;
}

static void	sleeping(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->data->dead_mutex);
	is_dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if ((philo->eat_count >= philo->data->max_eat && philo->data->max_eat >= 0)
		|| is_dead)
		return ;
	pprint_state(philo, STATE_SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(philo->data->time_to_eat / 2 * 1000);
	pthread_mutex_lock(&philo->data->dead_mutex);
	while (!philo->data->dead
		&& (philo->data->max_eat == -1
			|| philo->eat_count < philo->data->max_eat))
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		eating(philo);
		sleeping(philo);
		pprint_state(philo, STATE_THINKING);
		pthread_mutex_lock(&philo->data->dead_mutex);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (NULL);
}

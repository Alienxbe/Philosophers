/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:46:04 by marykman          #+#    #+#             */
/*   Updated: 2025/01/10 20:50:37 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"
#include <unistd.h>

unsigned long	get_time(struct timeval start_time)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_usec - start_time.tv_usec) / 1000
		+ (actual_time.tv_sec - start_time.tv_sec) * 1000);
}

void	pprint_state(t_philo *philo, t_philo_state state)
{
	const char		*state_str[STATE_LEN];
	unsigned long	time;

	state_str[STATE_FORK_TAKEN] = "has taken a fork";
	state_str[STATE_EATING] = "is eating";
	state_str[STATE_SLEEPING] = "is sleeping";
	state_str[STATE_THINKING] = "is thinking";
	state_str[STATE_DEAD] = "died";
	time = get_time(philo->data->start_time);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!(philo->data->dead))
		printf("%ld %d %s\n", time, philo->id, state_str[state]);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

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

static int	init_data(t_data *data)
{
	int	ret;
	int	i;

	ret = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->philos || !data->forks)
		return (1);

	// Init Mutex
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);

	// Init Philos
	i = -1;
	while (++i < data->philo_count && !ret){
		data->philos[i].id = i;
		gettimeofday(&data->philos[i].last_meal, NULL);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		data->philos[i].data = data;
	}

	// Init time
	gettimeofday(&data->start_time, NULL);

	// Init threads
	i = -1;
	while (++i < data->philo_count)
		pthread_create(&data->philos[i].t, NULL, &routine, &data->philos[i]);

	// Rejoin Philos
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(data->philos[i].t, NULL))
			return (1);
	return (ret);
}

int main(int argc, char const **argv)
{
	t_data	data;

	data = (t_data){0};
	if (parse_arguments(argc, argv, &data))
	{
		printf("%s\n", USAGE_STR);
		return (1);
	}
	if (argc == 6 && !data.max_eat)
		return (0);
	if (init_data(&data))
	{
		free(data.philos);
		return (1);
	};
	free(data.philos);
	return (0);
}

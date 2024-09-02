/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:46:04 by marykman          #+#    #+#             */
/*   Updated: 2024/09/02 18:26:00 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	*say_hi(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Hi\n");
	return (NULL);
}

static int	init_philo(t_philo *philo)
{
	int	ret;
	int	i;

	ret = 0;
	philo->t = (pthread_t *)malloc(sizeof(pthread_t) * philo->philo_count);
	if (!philo->t)
		return (1);
	pthread_mutex_init(&philo->mutex_print, NULL);
	i = -1;
	while (++i < philo->philo_count && !ret){
		printf("New philo %d\n", i);
		if (pthread_create(&philo->t[i], NULL, &say_hi, philo))
			ret = 1;
	}
	while (i >= 0)
		if (pthread_join(philo->t[i--], NULL))
			return (1);
	return (ret);
}

int main(int argc, char const **argv)
{
	t_philo	philo;

	philo = (t_philo){0};
	if (parse_arguments(argc, argv, &philo))
	{
		printf("%s\n", USAGE_STR);
		return (1);
	}
	if (init_philo(&philo))
	{
		free(philo.t);
		return (1);
	};
	free(philo.t);
	pthread_mutex_destroy(&philo.mutex_print);
	return (0);
}

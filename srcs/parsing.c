/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:43:28 by marykman          #+#    #+#             */
/*   Updated: 2024/09/02 18:01:05 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

static int	parse_str(const char *str)
{
	char	*endptr;
	int		n;

	n = ft_strtol(str, &endptr, BASE_DECI);
	if (!str || ft_strlen(str) != (size_t)(endptr - str)
		|| !*str)
		return (-1);
	return (n);
}

int	parse_arguments(int argc, const char **argv, t_philo *philo)
{
	if (argc < 5 || argc > 6)
		return (1);
	philo->philo_count = parse_str(argv[1]);
	philo->time_to_die = parse_str(argv[2]);
	philo->time_to_eat = parse_str(argv[3]);
	philo->time_to_sleep = parse_str(argv[4]);
	philo->max_eat = -1;
	if (argc == 6)
		philo->max_eat = parse_str(argv[5]);
	if (philo->philo_count < 0
		|| philo->time_to_die < 0
		|| philo->time_to_eat < 0
		|| philo->time_to_sleep < 0
		|| (philo->max_eat < 0 && argc == 6))
		return (1);
	return (0);
}

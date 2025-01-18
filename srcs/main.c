/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:46:04 by marykman          #+#    #+#             */
/*   Updated: 2025/01/18 01:43:59 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

static void	single_case(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%d 1 died\n", data->time_to_die);
}

int	main(int argc, char const **argv)
{
	t_data	data;

	data = (t_data){0};
	if (parse_arguments(argc, argv, &data))
	{
		printf("%s\n", USAGE_STR);
		return (1);
	}
	if ((argc == 6 && !data.max_eat) || !data.philo_count)
		return (0);
	if (data.philo_count == 1)
	{
		single_case(&data);
		return (0);
	}
	if (init_data(&data))
	{
		destroy_data(&data);
		return (1);
	}
	destroy_data(&data);
	return (0);
}

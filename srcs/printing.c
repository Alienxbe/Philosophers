/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:02:26 by marykman          #+#    #+#             */
/*   Updated: 2025/01/13 19:04:06 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"
#include "philo.h"

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
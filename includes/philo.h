/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:44:58 by marykman          #+#    #+#             */
/*   Updated: 2024/09/02 18:16:53 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define USAGE_STR		"Usage: ./philo <philo_count> <time_to_die> \
<time_to_eat> <time_to_sleep> [max_eat]"
# define THREAD_COUNT	4

# include <pthread.h>

typedef enum e_philo_state
{
	STATE_NONE = -1,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_WAITING,
	STATE_DEAD,
	STATE_LEN
}	t_philo_state;

typedef struct s_philo
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	pthread_t		*t;
	pthread_mutex_t	mutex_print;
}	t_philo;

int	parse_arguments(int argc, const char **argv, t_philo *philo);

#endif

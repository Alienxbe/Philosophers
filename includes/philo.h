/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:44:58 by marykman          #+#    #+#             */
/*   Updated: 2025/01/18 01:18:39 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USAGE_STR		"Usage: ./philo <philo_count> <time_to_die> \
<time_to_eat> <time_to_sleep> [max_eat]"

# include <pthread.h>
# include <sys/time.h>
# include <stdatomic.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef enum e_philo_state
{
	STATE_FORK_TAKEN,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_DEAD,
	STATE_LEN
}	t_philo_state;

struct s_philo
{
	int				id;
	int				eat_count;
	struct timeval	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		t;
	t_data			*data;
};

struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				philo_count;
	int				dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	struct timeval	start_time;
};

void	*routine(void *arg);
void	monitoring(t_data *data);
void	pprint_state(t_philo *philo, t_philo_state state);
int		init_data(t_data *data);
void	destroy_data(t_data *data);
int		parse_arguments(int argc, const char **argv, t_data *data);

#endif

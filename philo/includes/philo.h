/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:08 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/03 20:16:53 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# include <bits/types.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 250
# define USAGE \
	"usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
\n[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		time_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	unsigned int		nb_philos;
	int					must_eat_count;
	time_t				time_to_eat;
	time_t				time_to_die;
	time_t				time_to_sleep;
	time_t				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		stop_lock;
	pthread_mutex_t		write_lock;
	pthread_t			monitor;
	bool				sim_stop;
	t_philo				**philos;
}						t_table;

t_table					*init_table(int argc, char **argv);
t_philo					**init_philo(t_table *table);
bool					ft_isdigit(char *str);
time_t					get_time_in_ms(void);
void					cleanup(t_table *table);
int						ft_atoi(char *str);
#endif
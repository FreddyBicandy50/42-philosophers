/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:08 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/28 01:07:20 by fbicandy         ###   ########.fr       */
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

# define DEBUG_BANNER 1
# define MAX_PHILOS 250
# define USAGE \
	"usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_table	t_table;
typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	time_t				start_sim;
	long				meals_eaten;
	long				last_meal_time;
	bool				ate_full_meals;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	time_t				start_simulation;
	bool				has_simulation_end;
	bool				all_philos_ready;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		meal_lock;
}						t_table;

//						safety
void					dprint(char *msg);
void					exit_safe(char *msg);
void					mem_clear(void *data);
void					*safe_malloc(size_t bytes);
void					wait_all_philos(t_table *table);

//						philos
void					create_philos(t_table *table);

//						manage
bool					all_philos_ate_enough(t_table *table);
void					*death_monitor(void *data);
void					print_status(t_philo *philo, char *status);
bool					has_sim_stopped(t_table *table);

//						parsing
int						ft_atoi(char *str);
void					validate_parsing(char **argv);

//						utils
time_t					get_time_in_ms(void);

//						init_table
void					init_table(t_table **table, int argc, char *argv[]);
#endif
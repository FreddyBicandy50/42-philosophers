/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:08 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/07 19:58:57 by fbicandy         ###   ########.fr       */
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
[number_of_times_each_philosopher_must_eat]\n"
typedef struct s_table	t_table;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKNIG,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DIED,
}						t_philo_status;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	t_fork				*left_fork;
	t_fork				*right_fork;
	time_t				start_sim;
	long				ate_meals_counter;
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
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
}						t_table;

//						safety
void					exit_safe(char *msg);
void					mem_clear(void *data);
void					*safe_malloc(size_t bytes);
void					write_status(char *msg, t_philo *philo);

//						parsing
int						ft_atoi(char *str);
void					validate_parsing(char **argv);

//						philo
void					join_philo(t_table *table);
void					create_philo(t_table *table);
void					*philosopher_routine(void *data);

//						utils
time_t					get_time_in_ms(void);
bool					has_sim_ended(t_table *table);
bool					wait_all_threads(t_table *table);

//						init
void					init_table(t_table **table, int argc, char *argv[]);
#endif
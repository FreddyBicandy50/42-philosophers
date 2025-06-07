/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:08 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/06 16:07:04 by fbicandy         ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	pthread_t			thread_id;
	int					id;
	t_fork				*left_fork;
	t_fork				*right_fork;
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
 	t_fork				*forks;
	t_philo				*philos;
}						t_table;

void					sync_all_threads(t_table *table);
void					mem_clear(void *data);
void					exit_safe(char *msg);
void					*saffe_malloc(size_t bytes);

int						ft_atoi(char *str);
void					validate_parsing(char **argv);

void					init_table(t_table **table, int argc, char *argv[]);
#endif
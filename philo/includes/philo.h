/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 22:00:00 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/28 22:45:48 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 250
# define DEBUG_BANNER 0
# define USAGE "Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	bool			ate_full_meals;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long long		start_simulation;
	bool			all_philos_ready;
	bool			has_simulation_end;
	int				philos_initialized;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_table;

/* main.c */
void				join_all_philosophers(t_table *table);
void				monitor_meals(t_table *table);
void				*death_monitor(void *data);
void				start_simulation(t_table *table);

/* init_table.c */
void				init_table(t_table **table, int argc, char *argv[]);
void				init_forks(t_table **table, int nb_philos);
void				init_philo(t_table **table, int nb_philos);

/* parsing.c */
void				validate_parsing(char **argv);
int					ft_atoi(char *str);
void				does_containes_only_digits(char *str);

/* philo.c */
void				create_philos(t_table *table);
void				*philos_routine(void *data);
void				eat(t_philo *philo);
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);

/* manage.c */
bool				has_sim_stopped(t_table *table);
void				wait_all_philos(t_table *table);
void				print_status(t_philo *philo, char *status);
bool				is_philosopher_dead(t_philo *philo);
bool				all_philos_ate_enough(t_table *table);

/* utils.c */
long long			get_time_in_ms(void);
void				ft_usleep(long long time_in_ms);

/* safety.c */
void				dprint(char *msg);
void				exit_safe(char *msg);
void				mem_clear(void *data);
void				*safe_malloc(size_t bytes);
bool				ate_full_meals(t_philo *philo);

#endif
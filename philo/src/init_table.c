/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:26:09 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/08 15:47:32 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philo(t_table **table, int nb_philos)
{
	int	i;

	(*table)->philos = safe_malloc(sizeof(t_philo) * nb_philos);
	if (!(*table)->philos)
		exit_safe("Failed to allocate philosophers");
	i = -1;
	while (++i < nb_philos)
	{
		(*table)->philos[i].id = i + 1;
		(*table)->philos[i].table = *table;
		(*table)->philos[i].last_meal_time = 0;
		(*table)->philos[i].meals_eaten = 0;
		(*table)->philos[i].ate_full_meals = false;
		(*table)->philos[i].left_fork = &(*table)->forks[i];
		(*table)->philos[i].right_fork = &(*table)->forks[(i + 1) % nb_philos];
	}
	dprint("\tall philos chairs have been initialised successfully...");
}

void	init_forks(t_table **table, int nb_philos)
{
	int	i;

	i = -1;
	(*table)->forks = safe_malloc(sizeof(pthread_mutex_t) * nb_philos);
	while (++i < nb_philos)
		pthread_mutex_init(&(*table)->forks[i], NULL);
	dprint("\tall forks has been initialised successfully...");
}

void	init_table(t_table **table, int argc, char *argv[])
{
	int	i;

	i = 1;
	(*table) = safe_malloc(sizeof(t_table));
	pthread_mutex_init(&(*table)->table_mutex, NULL);
	pthread_mutex_init(&(*table)->write_mutex, NULL);
	pthread_mutex_init(&(*table)->meal_lock, NULL);
	(*table)->number_of_philos = ft_atoi(argv[i++]);
	(*table)->time_to_die = ft_atoi(argv[i++]);
	(*table)->time_to_eat = ft_atoi(argv[i++]);
	(*table)->time_to_sleep = ft_atoi(argv[i++]);
	(*table)->number_of_meals = -1;
	if (argc == 5)
		(*table)->number_of_meals = ft_atoi(argv[i]);
	(*table)->start_simulation = 0;
	(*table)->all_philos_ready = false;
	(*table)->has_sim_stopped = false;
	(*table)->philos_initialized = 0;
	init_forks(table, (*table)->number_of_philos);
	init_philo(table, (*table)->number_of_philos);
	dprint("Table has been initialised successfully...");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:26:49 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/28 19:53:36 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	join_all_philosophers(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
		pthread_join(table->philos[i].thread_id, NULL);
}

void	monitor_simulation_end(t_table *table)
{
	while (!has_sim_stopped(table))
	{
		if (table->number_of_meals > 0 && all_philos_ate_enough(table))
		{
			pthread_mutex_lock(&table->table_mutex);
			table->has_simulation_end = true;
			pthread_mutex_unlock(&table->table_mutex);
			break ;
		}
	}
	usleep(1000);
}

void	start_simulation(t_table *table)
{
	pthread_t	death_monitor_thread;

	if (table->number_of_meals == 0)
		return ;
	if (table->number_of_philos == 1)
		return ; // TODO:: handle lone philo
	table->start_simulation = get_time_in_ms();
	create_philos(table);
	pthread_mutex_lock(&table->table_mutex);
	table->all_philos_ready = true;
	pthread_mutex_unlock(&table->table_mutex);
	// Create death monitor thread
	if (pthread_create(&death_monitor_thread, NULL, death_monitor, table) != 0)
		return (mem_clear(table),
			exit_safe("Failed to create death monitor thread"));
	// Wait for simulation to end (death or all ate enough)
	monitor_simulation_end(table);
	pthread_join(death_monitor_thread, NULL);
	join_all_philosophers(table);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	(void)*argv;
	(void)argc;
	if (DEBUG_BANNER == 1)
		dprint("!!!!SHOWING DEUBG MESSAGE!!!!");
	table = NULL;
	argc = argc - 1;
	if (argc < 4 || argc > 5)
		return (printf("%s", USAGE), 1);
	validate_parsing(argv);
	init_table(&table, argc, argv);
	start_simulation(table);
	if (table)
		mem_clear(table);
	return (0);
}

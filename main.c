/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:26:49 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/08 15:47:46 by fbicandy         ###   ########.fr       */
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

void	monitor_simulation(t_table *table)
{
	int	i;
	int	philos_init;

	philos_init = 0;
	while (philos_init < table->number_of_philos)
	{
		pthread_mutex_lock(&table->table_mutex);
		philos_init = table->philos_initialized;
		pthread_mutex_unlock(&table->table_mutex);
		if (philos_init < table->number_of_philos)
			usleep(100);
	}
	while (!has_sim_stopped(table))
	{
		i = -1;
		while (++i < table->number_of_philos)
			if (is_philosopher_dead(&table->philos[i]))
				return (sim_stop(true, &table, i));
		if (table->number_of_meals > 0 && all_philos_ate_enough(table))
			return (sim_stop(false, &table, i));
		usleep(1000);
	}
}

void	start_simulation(t_table *table)
{
	if (table->number_of_meals == 0)
		return ;
	if (table->number_of_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(table->time_to_die * 1000);
		printf("%d 1 died\n", table->time_to_die);
		return ;
	}
	table->start_simulation = get_time_in_ms();
	create_philos(table);
	pthread_mutex_lock(&table->table_mutex);
	table->all_philos_ready = true;
	pthread_mutex_unlock(&table->table_mutex);
	monitor_simulation(table);
	join_all_philosophers(table);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (DEBUG_BANNER == 1)
		dprint("!!!!SHOWING DEBUG MESSAGE!!!!");
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

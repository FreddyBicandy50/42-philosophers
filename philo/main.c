/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:26:49 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/11 21:28:59 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	start_simulation(t_table *table)
{
	if (table->number_of_meals == 0)
		return ;
	if (table->number_of_philos == 1)
	{
		// TODO: handle solo philosopher case properly
		return ;
	}
	create_philo(table); // resume
	exit(0);
	pthread_mutex_lock(&table->table_mutex);
	table->all_philos_ready = true;
	pthread_mutex_unlock(&table->table_mutex);
	table->start_simulation = get_time_in_ms();
	join_philo(table);
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
	start_simulation(table); // resume...
	exit(0);
	if (table)
		mem_clear(table);
	return (0);
}

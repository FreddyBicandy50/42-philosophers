/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:26:49 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/06 16:12:03 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*philosopher_routine(void *data)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)data;
	
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_of_meals == 0)
		return ;
	if (table->number_of_philos == 1)
		; // TODO:: handle lone philo
	else
		while (++i < table->number_of_philos)
			if (pthread_create(&table->philos[i], philosopher_routine,
					&table->philos[i], NULL) != 0)
				return (exit("error while creating threads!"),
					mem_clear(table));
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	(void)*argv;
	(void)argc;
	table = NULL;
	argc = argc - 1;
	if (argc < 4 || argc > 5)
		return (printf("%s", USAGE), 1);
	validate_parsing(argv);
	init_table(&table, argc, argv);
	start_simuilation(table);
	if (table)
		mem_clear(table);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:44:51 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/06 16:02:29 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void 	exit_safe(char *msg)
{
	return (printf("%s", msg), exit(EXIT_FAILURE));
}

void	mem_clear(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	free(table);
}


void sync_all_threads(t_table *table)
{

}


void	*safe_malloc(size_t bytes)
{
	void *memorie_allocated;

	memorie_allocated = malloc(bytes);
	if (!memorie_allocated)
		return (exit_safe("error while malloc!"),NULL);
	return (memorie_allocated);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:44:51 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/08 15:47:41 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ate_full_meals(t_philo *philo)
{
	if (philo->table->number_of_meals > 0
		&& philo->meals_eaten >= philo->table->number_of_meals)
	{
		pthread_mutex_lock(&philo->table->meal_lock);
		philo->ate_full_meals = true;
		pthread_mutex_unlock(&philo->table->meal_lock);
		return (true);
	}
	return (false);
}

void	sim_stop(bool died, t_table **table, int index)
{
	if (died && !((*table)->number_of_meals > 0))
		print_status(&(*table)->philos[index], "died");
	pthread_mutex_lock(&(*table)->table_mutex);
	(*table)->has_sim_stopped = true;
	pthread_mutex_unlock(&(*table)->table_mutex);
}

void	exit_safe(char *msg)
{
	return (printf("%s", msg), exit(EXIT_FAILURE));
}

void	mem_clear(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	if (table->forks)
	{
		i = -1;
		while (++i < table->number_of_philos)
			pthread_mutex_destroy(&table->forks[i]);
		free(table->forks);
	}
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->meal_lock);
	if (table->philos)
		free(table->philos);
	free(table);
}

void	*safe_malloc(size_t bytes)
{
	void	*memorie_allocated;

	memorie_allocated = malloc(bytes);
	if (!memorie_allocated)
		return (exit_safe("error while malloc!"), NULL);
	return (memorie_allocated);
}

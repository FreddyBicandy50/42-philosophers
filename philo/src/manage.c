/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:56:16 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/28 01:04:53 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	all_philos_ate_enough(t_table *table)
{
	int	i;

	i = -1;
	exit(0);
	pthread_mutex_lock(&table->meal_lock);
	while (++i < table->number_of_philos)
		if (table->philos[i].meals_eaten < table->number_of_meals)
			return ((pthread_mutex_unlock(&table->meal_lock)), false);
	pthread_mutex_unlock(&table->meal_lock);
	return (true);
}

bool	is_philosopher_dead(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->table->meal_lock);
	current_time = get_time_in_ms();
	time_since_last_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->meal_lock);
	if (time_since_last_meal >= philo->table->time_to_die)
		return (true);
	return (false);
}

void	*death_monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (!has_sim_stopped(table))
	{
		for (int i = 0; i < table->number_of_philos; i++)
		{
			if (is_philosopher_dead(&table->philos[i]))
			{
				print_status(&table->philos[i], " has died");
				pthread_mutex_lock(&table->table_mutex);
				table->has_simulation_end = true;
				pthread_mutex_unlock(&table->table_mutex);
				return (NULL);
			}
		}
		usleep(1000); // Check every 1ms
	}
	return (NULL);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	timestamp = get_time_in_ms() - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (!has_sim_stopped(philo->table))
		printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

bool	has_sim_stopped(t_table *table)
{
	pthread_mutex_lock(&table->table_mutex);
	if (table->has_simulation_end)
		return (pthread_mutex_unlock(&table->table_mutex), 1);
	return (pthread_mutex_unlock(&table->table_mutex), 0);
}

void	wait_all_philos(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->all_philos_ready)
		{
			pthread_mutex_unlock(&table->table_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->table_mutex);
		usleep(100);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:56:16 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/05 14:08:29 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	all_philos_ate_enough(t_table *table)
{
	int		i;
	bool	all_ate;

	i = -1;
	all_ate = true;
	pthread_mutex_lock(&table->meal_lock);
	while (++i < table->number_of_philos)
	{
		if (!table->philos[i].ate_full_meals)
		{
			all_ate = false;
			break ;
		}
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (all_ate);
}

bool	is_philosopher_dead(t_philo *philo)
{
	long long	current_time;
	long long	time_since_last_meal;
	bool		should_die;

	should_die = false;
	pthread_mutex_lock(&philo->table->meal_lock);
	current_time = get_time_in_ms();
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal > philo->table->time_to_die
		&& !philo->table->has_sim_stopped)
	{
		should_die = true;
		// Mark simulation as stopped while still holding the lock
		pthread_mutex_lock(&philo->table->table_mutex);
		philo->table->has_sim_stopped = true;
		pthread_mutex_unlock(&philo->table->table_mutex);
		// Print death message while preventing other prints
		pthread_mutex_lock(&philo->table->write_mutex);
		printf("%lld %d died\n", current_time - philo->table->start_simulation,
			philo->id);
		pthread_mutex_unlock(&philo->table->write_mutex);
	}
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (should_die);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->table->write_mutex);
	if (!has_sim_stopped(philo->table))
	{
		timestamp = get_time_in_ms() - philo->table->start_simulation;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->write_mutex);
}

bool	has_sim_stopped(t_table *table)
{
	bool	stopped;

	pthread_mutex_lock(&table->table_mutex);
	stopped = table->has_sim_stopped;
	pthread_mutex_unlock(&table->table_mutex);
	return (stopped);
}

void	wait_all_philos(t_table *table)
{
	bool	ready;

	ready = false;
	while (!ready)
	{
		pthread_mutex_lock(&table->table_mutex);
		ready = table->all_philos_ready;
		pthread_mutex_unlock(&table->table_mutex);
		if (!ready)
			usleep(100);
	}
}

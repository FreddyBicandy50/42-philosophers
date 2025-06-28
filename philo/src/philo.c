/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:24:00 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/28 20:06:42 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, " has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, " has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, " has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, " has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_lock);
	usleep(philo->table->time_to_eat * 1000); // <-- FIX HERE
	drop_forks(philo);
}

void	*philos_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->table->meal_lock);
	while (!has_sim_stopped(philo->table))
	{
		print_status(philo, "is thinking");
		eat(philo);
		if (philo->table->number_of_meals > 0
			&& philo->meals_eaten >= philo->table->number_of_meals)
		{
			philo->ate_full_meals = true;
			break ;
		}
		print_status(philo, "is sleeping");
		usleep(philo->table->time_to_sleep * 1000);
	}
	return (NULL);
}

void	create_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, philos_routine,
				&table->philos[i]) != 0)
			return (mem_clear(table),
				exit_safe("error while creating threads"));
	}
	dprint("all philos created succesfully");
}

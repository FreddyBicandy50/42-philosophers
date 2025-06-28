/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:24:00 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/28 22:45:22 by fbicandy         ###   ########.fr       */
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
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
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
	ft_usleep(philo->table->time_to_eat);
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
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->table->philos_initialized++;
	pthread_mutex_unlock(&philo->table->table_mutex);
	if (philo->id % 2 == 0)
		usleep(500);
	while (!has_sim_stopped(philo->table))
	{
		print_status(philo, "is thinking");
		eat(philo);
		if (ate_full_meals(philo))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
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
	dprint("all philos created successfully");
}

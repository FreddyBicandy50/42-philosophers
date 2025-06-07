/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:24:00 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/07 20:04:44 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	write_status(TAKE_LEFT_FORK, philo);
	pthread_mutex_unlock(&philo->left_fork);
}

void	*philosopher_routine(void *data)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)data;
	wait_all_threads(philosopher->table);
	while (!has_sim_ended(philosopher->table))
	{
		if (philosopher->ate_full_meals)
			break ;
		eat(philosopher);
		// sleep
		think(philosopher);
	}
	return (NULL);
}

void	create_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		table->philos[i].start_sim = get_time_in_ms();
		if (pthread_create(&table->philos[i].thread_id, NULL,
				philosopher_routine, &table->philos[i]) != 0)
		{
			return (mem_clear(table),
				exit_safe("error while creating threads!"));
		}
	}
}

void	join_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			return (mem_clear(table),
				exit_safe("error while wating philos to join"));
}

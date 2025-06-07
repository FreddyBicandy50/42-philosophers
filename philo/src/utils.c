/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:56:01 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/07 19:32:26 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	precise_usleep(long usec, t_table *table)
{
	time_t	start;
	time_t	elapsed;
	time_t	rem;

	start = get_time_in_us();
	while (get_time_in_us() - start < usec)
	{
		if (has_sim_ended(table))
			break ;
		elapsed = get_time_in_us();
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time_in_us() - start < usec)
				;
		}
	}
}

/*
 * we'll check if the sim has already ended
 */
bool	has_sim_ended(t_table *table)
{
	pthread_mutex_lock(&table->table_mutex);
	if (table->has_simulation_end)
		return (pthread_mutex_unlock(&table->table_mutex), true);
	else
		return (pthread_mutex_unlock(&table->table_mutex), false);
}

/*
 * we'll wait for all philos to be created before we start
 */
bool	wait_all_threads(t_table *table)
{
	pthread_mutex_lock(&table->table_mutex);
	if (table->all_philos_ready)
		return (pthread_mutex_unlock(&table->table_mutex), true);
	else
		return (pthread_mutex_unlock(&table->table_mutex), false);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	get_time_in_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((time_t)tv.tv_sec * 1000000 + tv.tv_usec);
}

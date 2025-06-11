/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:44:51 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/11 20:46:08 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	dprint(char *msg)
{
	if (DEBUG_BANNER)
		printf("%s\n", msg);
}

void	exit_safe(char *msg)
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

void	*safe_malloc(size_t bytes)
{
	void	*memorie_allocated;

	memorie_allocated = malloc(bytes);
	if (!memorie_allocated)
		return (exit_safe("error while malloc!"), NULL);
	return (memorie_allocated);
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time_in_ms() - philo->start_sim;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (TAKE_LEFT_FORK == status || TAKE_RIGHT_FORK == status
		|| !has_sim_ended(philo->table))
		printf("[%ld] %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status || !has_sim_ended(philo->table))
		printf("[%ld] %d is eating\n", elapsed, philo->id);
	else if (THINKNIG == status || !has_sim_ended(philo->table))
		printf("[%ld] %d is thinknig\n", elapsed, philo->id);
	else if (DIED == status)
		printf("[%ld] %d is died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

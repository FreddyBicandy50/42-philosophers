/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logistics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:00:03 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/03 20:08:18 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < (int)table->nb_philos)
	{
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	free(table->forks);
	free(table);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

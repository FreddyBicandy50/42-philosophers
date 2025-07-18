/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:56:01 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/08 15:47:42 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	dprint(char *msg)
{
	if (DEBUG_BANNER == 1)
		printf("%s\n", msg);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time_in_ms)
{
	long long		elapsed;
	long long		remaining;
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		elapsed = ((current.tv_sec - start.tv_sec) * 1000) + ((current.tv_usec
					- start.tv_usec) / 1000);
		if (elapsed >= time_in_ms)
			break ;
		remaining = time_in_ms - elapsed;
		if (remaining > 1)
			usleep((remaining * 1000) / 2);
		else
			usleep(50);
	}
}

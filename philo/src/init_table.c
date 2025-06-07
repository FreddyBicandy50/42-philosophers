/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:51:55 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/06 15:52:17 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:18:08 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/03 15:28:55 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	assgin_forks(t_table **table, int position)
{
	int		nb_philos;
	t_fork	*left_fork;
	t_fork	*right_fork;

	nb_philos = (*table)->number_of_philos;
	left_fork = &(*table)->forks[(position + 1) % nb_philos];
	right_fork = &(*table)->forks[position];
	if ((*table)->philos[position].id % 2 == 0)
	{
		(*table)->philos[position].right_fork = right_fork;
		(*table)->philos[position].left_fork = left_fork;
	}
	else
	{
		(*table)->philos[position].left_fork = left_fork;
		(*table)->philos[position].right_fork = right_fork;
	}
	return ;
}

void	init_philo(t_table **table)
{
	int		i;

	i = 0;
	(*table)->philos = safe_malloc(sizeof(t_philo)
			* (*table)->number_of_philos);
	while (i < (*table)->number_of_philos)
	{
		(*table)->philos[i].id = i + 1;
		assgin_forks(table, i);
		(*table)->philos[i].ate_meals_counter = 0;
		(*table)->philos[i].ate_full_meals = false;

		i++;
	}
}

void	init_forks(t_table **table)
{
	int	i;

	i = 0;
	(*table)->forks = safe_malloc(sizeof(t_fork) * (*table)->number_of_philos);
	while (i < (*table)->number_of_philos)
	{
		pthread_mutex_init(&(*table)->forks[i].fork, NULL);
		(*table)->forks->fork_id = i;
		i++;
	}
}

void	init_table(t_table **table, int argc, char *argv[])
{
	int	i;

	i = 1;
	(*table) = safe_malloc(sizeof(t_philo));
	(*table)->number_of_philos = ft_atoi(argv[i++]) * 1000;
	init_forks(table);
	init_philo(table);
	(*table)->time_to_die = ft_atoi(argv[i++]) * 1000;
	(*table)->time_to_eat = ft_atoi(argv[i++]) * 1000;
	(*table)->time_to_sleep = ft_atoi(argv[i++]) * 1000;
	(*table)->number_of_meals = -1;
	if (argc == 5)
		(*table)->number_of_meals = ft_atoi(argv[i]);
}

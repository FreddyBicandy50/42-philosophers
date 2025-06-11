/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:26:09 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/11 21:21:21 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	assign_forks(t_table **table, int position)
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

void	init_philo(t_table **table, int nb_philos)
{
	int	i;

	(*table)->philos = safe_malloc(sizeof(t_philo) * nb_philos);
	if (!(*table)->philos)
		exit_safe("Failed to allocate philosophers");
	i = 0;
	while (i < nb_philos)
	{
		(*table)->philos[i].id = i + 1;
		(*table)->philos[i].table = *table;
		(*table)->philos[i].ate_meals_counter = 0;
		(*table)->philos[i].ate_full_meals = false;
		assign_forks(table, i);
		i++;
	}
	dprint("\tall philos chairs have been initialised successfully...");
}

void	init_forks(t_table **table, int nb_philos)
{
	int	i;

	i = 0;
	(*table)->forks = safe_malloc(sizeof(t_fork) * nb_philos);
	while (i < nb_philos)
	{
		pthread_mutex_init(&(*table)->forks[i].lock, NULL);
		(*table)->forks->fork_id = i;
		i++;
	}
	dprint("\tall forks has been initialised successfully...");
}

void	init_table(t_table **table, int argc, char *argv[])
{
	int	i;

	i = 1;
	(*table) = safe_malloc(sizeof(t_table));
	pthread_mutex_init(&(*table)->table_mutex, NULL);
	pthread_mutex_init(&(*table)->write_mutex, NULL);
	(*table)->all_philos_ready = false;
	(*table)->number_of_philos = ft_atoi(argv[i++]);
	(*table)->time_to_die = ft_atoi(argv[i++]) * 1000;
	(*table)->time_to_eat = ft_atoi(argv[i++]) * 1000;
	(*table)->time_to_sleep = ft_atoi(argv[i++]) * 1000;
	(*table)->number_of_meals = -1;
	if (argc == 5)
		(*table)->number_of_meals = ft_atoi(argv[i]);
	init_philo(table, (*table)->number_of_philos);
	init_forks(table, (*table)->number_of_philos);
	dprint("Table has been initialised successfully...");
}

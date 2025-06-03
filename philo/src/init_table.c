/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:12:53 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/02 17:43:45 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	valid(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		str++;
	}
	return (true);
}

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	if (!valid(str))
		return (-1);
	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

pthread_mutex_t	*init_mutexes(t_table **table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * (*table)->nb_philos);
	if (!forks)
		return (printf("malloc error!"), NULL);
	while (i < (int)(*table)->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (ft_error("error mutex initialise", (void **)&forks), NULL);
		i++;
	}
	if (pthread_mutex_init(&(*table)->write_lock, 0) != 0
		|| pthread_mutex_init(&(*table)->stop_lock, 0) != 0)
		return (NULL);
	(*table)->sim_stop = false;
	return (forks);
}

t_philo	**init_philo(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table)
		return (printf("malloc error!"), NULL);
	i = -1;
	while (++i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0)
			|| !philos[i] != 0)
			return (ft_error("malloc error!", (void **)&philos), NULL);
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->time_ate = 0;
		philos[i]->fork[0] = i;
		philos[i]->fork[1] = (i + 1) % table->nb_philos;
		if (i % 2 == 0)
		{
			philos[i]->fork[0] = (i + 1) % table->nb_philos;
			philos[i]->fork[1] = i;
		}
	}
	return (philos);
}

t_table	*init_table(int argc, char **argv)
{
	int		i;
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("malloc error!"), NULL);
	i = 1;
	if (ft_atoi(argv[i]) == 0)
		return (ft_error("error ./philo: number of philosophers cannot be zero",
				(void **)&table), NULL);
	while (i < argc)
		if (ft_atoi(argv[i++]) <= -1)
			return (ft_error("error ./philo: negative values not allowed\n",
					(void **)&table), NULL);
	i = 1;
	table->nb_philos = ft_atoi(argv[i++]);
	table->time_to_die = ft_atoi(argv[i++]);
	table->time_to_eat = ft_atoi(argv[i++]);
	table->time_to_sleep = ft_atoi(argv[i++]);
	table->must_eat_count = -1;
	if (argc == 5)
		table->must_eat_count = ft_atoi(argv[i]);
	table->philos = init_philo(table);
	table->forks = init_mutexes(&table);
	return (table);
}

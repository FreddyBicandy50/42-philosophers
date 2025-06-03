/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:26:49 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/03 20:38:52 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	has_simulation_stopped(t_table *table)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&table->stop_lock);
	if (table->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&table->stop_lock);
	return (r);
}

void	monitor(void)
{
}

void	philo_routine(t_philo *data)
{
	t_philo	*philosopher;

	philosopher = data;
	if (philosopher->table->must_eat_count == 0)
		return ;
	pthread_mutex_lock(&philosopher->meal_time_lock);
	philosopher->last_meal = philosopher->table->start_time;
	pthread_mutex_unlock(&philosopher->meal_time_lock);
	while (get_time_in_ms() < philosopher->table->start_time)
		continue ;
	if (philosopher->table->time_to_die == 0)
		return ;
	if (philosopher->table->nb_philos == 0)
		return (one_philo_handle(philosopher));
	else if (philosopher->id % 2 == 0)
		think_routine(philosopher, true);
	while (has_simulation_stopped(philosopher->table) == false)
	{
		eat_sleep_routine(philosopher);
		think_routine(philosopher, false);
	}
}

bool	start_sim(t_table *table)
{
	int	i;

	table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i], NULL, philo_routine,
				table->philos[i]) != 0)
			return ("error creating philo!", false);
		i++;
	}
	if (table->nb_philos > 1)
		if (pthread_create(table->monitor, NULL, monitor, table) != 0)
			return ("error creating monitor thread!", false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	(void)*argv;
	(void)argc;
	table = NULL;
	if (argc - 1 < 4 || argc - 1 > 5)
		return (printf("%s", USAGE), 1);
	table = init_table(argc - 1, argv);
	if (table == NULL)
		return (printf("\n%s", USAGE), 1);
	if (!table)
		return (cleanup(table), 1);
	// TODO:: sim start
	if (!start_sim(table))
		return (cleanup(table), 1);
	return (0);
}

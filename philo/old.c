/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:35:30 by fbicandy          #+#    #+#             */
/*   Updated: 2025/05/28 20:26:47 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/philo.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

void	*monitor(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		int i = 0; // ✅ reset i every iteration
		while (i < philos[0].data->n_philos)
		{
			if (!philos[0].data->dead && current_time_ms()
				- philos[i].last_meal > philos[i].data->time_to_die)
			{
				philos[0].data->dead = 1;
				pthread_mutex_lock(&philos[0].data->write_mutex);
				printf("[%lld] Philosopher %d died\n", current_time_ms()
					- philos[i].data->start_time, philos[i].id);
				pthread_mutex_unlock(&philos[0].data->write_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000); // check every 1ms
	}
	return (NULL);
}

void	smart_sleep(long long duration, t_data *data)
{
	long long	start;

	start = current_time_ms();
	while (!data->dead && current_time_ms() - start < duration)
		usleep(100); // short sleep chunks to allow checking dead flag
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->write_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->write_mutex);
			break ;
		}
		printf("[%lld] Philosopher %d is thinking...\n", current_time_ms()
			- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write_mutex);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		philo->last_meal = current_time_ms();
		pthread_mutex_lock(&philo->data->write_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->write_mutex);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		printf("[%lld] Philosopher %d is eating\n", current_time_ms()
			- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write_mutex);
		smart_sleep(1000, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->data->write_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->write_mutex);
			break ;
		}
		printf("[%lld] Philosopher %d is sleeping\n", current_time_ms()
			- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write_mutex);
		smart_sleep(1000, philo->data);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor_thread;
	int				i;
	t_data			data;

	philos = malloc(sizeof(t_philo) * data->n_philos);
	forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	data.time_to_die = 2000; // example value
	data.start_time = current_time_ms();
	data.n_philos = nb_philos;
	data.dead = 0;
	pthread_mutex_init(&data.write_mutex, NULL);
	i = 0;
	while (i < nb_philos)
	{
		// creating mutex on number of philos
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		philos[i].id = i + 1; // assign id for each philo
		philos[i].data = &data;
		// assigning forks
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % nb_philos];
		philos[i].last_meal = data.start_time;
		// create the thread
		if (pthread_create(&philos[i].philospher, NULL, routine,
				&philos[i]) != 0)
			return (perror("Failed to create thread"), 1);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor, philos);
	pthread_join(monitor_thread, NULL); // ← blocks immediately
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_join(philos[i].philospher, NULL) != 0)
			return (perror("Failed to join thread"), 1);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		for (int i = 0; i < nb_philos; i++)
			pthread_mutex_destroy(&forks[i]);
	}
	pthread_mutex_destroy(&data.write_mutex);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:26:49 by fbicandy          #+#    #+#             */
/*   Updated: 2025/06/02 17:49:10 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/philo.h"

void	ft_error(char *msg, void **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	printf("%s\n", msg);
	return ;
}

int	main(int argc, char *argv[])
{
	t_table *table;
	(void)*argv;
	(void)argc;

	table = NULL;
	if (argc - 1 < 4 || argc - 1 > 5)
		return (printf("%s", USAGE), 1);
	table = init_table(argc - 1, argv);
	if (table == NULL)
		return (printf("\n%s", USAGE), 1);
	int i = 0;
	while (i < (int)table->nb_philos)
	{
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	free(table->forks);
	free(table);
	return (0);
}
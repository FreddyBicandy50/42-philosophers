/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:42:18 by fbicandy          #+#    #+#             */
/*   Updated: 2025/05/12 20:16:30 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	contains_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

int	is_valid_input(int argc, char **argv)
{
	int nb;
	int i;

	if (argc - 1 < 4 || argc - 1 > 5)
		return (printf("%s", USAGE), EXIT_FAILURE);
	i = 1;
	while (i < argc)
	{
		if (!contains_only_digits(argv[i]))
			return (printf("invalid input \n %s", USAGE), EXIT_FAILURE);
		nb = ft_atoi(argv[i]);
		if (i == 1 && (nb <= 0 || nb > 250))
			return (printf("invalid number of philosophers\n"), EXIT_FAILURE);
		if (i != 1 && nb <= -1)
			return (printf("invalid input \n"), EXIT_FAILURE);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:50:50 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/08 15:47:39 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	does_containes_only_digits(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			exit_safe("only digits are accepted!");
		str++;
	}
	return ;
}

int	ft_atoi(char *str)
{
	long	result;
	int		i;

	does_containes_only_digits(str);
	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	validate_parsing(char **argv)
{
	int	i;
	int	nb;

	nb = ft_atoi(argv[1]);
	if (nb <= 0 || nb > MAX_PHILOS)
		exit_safe("error ./philo: number of philosophers should\
			be between 1 and 250\n");
	i = 1;
	while (i <= 3)
	{
		nb = ft_atoi(argv[i + 1]);
		if (nb > __INT_MAX__)
			exit_safe("error:number is grater than INT_MAX\n");
		if (nb <= -1)
			exit_safe("error:numbers cannot be negative\n");
		i++;
	}
	dprint("all arguments are valid...");
}

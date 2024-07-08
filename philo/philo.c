/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:14:29 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:42:25 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	freephilos(t_table *table)
{
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&table, av) == -1)
			return (-1);
		if (data_init(&table) == -1)
			return (freephilos(&table), -1);
		if (dinner_start(&table) == -1)
			return (clean(&table), -1);
		clean(&table);
	}
	else
		printf("Wrong input :\n" GREEN "Correct is ./philo 5 800 200 200 [5]");
}

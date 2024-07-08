/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:25:54 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:54:51 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static long	ft_atol2(const char *str, long retval)
{
	int	i;

	i = 0;
	while (*str >= '0' && *str <= '9')
	{
		retval = retval * 10 + (*str - '0');
		str++;
	}
	if (retval > INT_MAX)
	{
		printf("Give me a number between 0\
			and 2147483647");
		return (-1);
	}
	while (str[i] != '\0' && (str[i] < '0' || str[i++] > '9'))
	{
		printf("Give me only numbers");
		return (-1);
	}
	return (retval);
}

static long	ft_atol(const char *str)
{
	long	retval;

	retval = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		printf("Give me only positive numbers");
		return (-1);
	}
	if (*str < '0' || *str > '9')
	{
		printf("Give me only numbers");
		return (-1);
	}
	retval = ft_atol2(str, retval);
	return (retval);
}

static int	parse_input2(t_table *table, char **av)
{
	if (av[5])
	{
		table->num_limit_meals = ft_atol(av[5]);
		if (table->num_limit_meals == -1)
			return (-1);
	}
	else
		table->num_limit_meals = -1;
	return (0);
}

int	parse_input(t_table *table, char **av)
{
	table->philo_num = ft_atol(av[1]);
	if (table->philo_num == -1)
		return (-1);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	if (table->time_to_die == -1000)
		return (-1);
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	if (table->time_to_eat == -1000)
		return (-1);
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_sleep == -1000)
		return (-1);
	if (parse_input2(table, av) == -1)
		return (-1);
	return (0);
}

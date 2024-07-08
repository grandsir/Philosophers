/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 04:01:39 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:53:46 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

long	gettime(int time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (time_code == MSEC)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (time_code == USEC)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (time_code == SECONDS)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		error_exit("Wrong input to gettime:"
			"use <MSEC> <USEC> <SECONDS>");
	return (1453);
}

#include <stdio.h> 
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(USEC);
	while (gettime(USEC) - start < usec)
	{
		if (sim_finished(table))
			break ;
		elapsed = gettime(USEC) - start;
		rem = usec - elapsed;
		if (rem > 10000)
		{
			usleep(rem / 2);
		}
		else
			while (gettime(USEC) - start < usec)
				;
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		mutex_operation(&philo->philo_mutex, DESTROY);
	}
	mutex_operation(&table->write_mutex, DESTROY);
	mutex_operation(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

int	error_exit(const char *error)
{
	printf(RED "! %s !\n" RESET, error);
	return (-1);
}

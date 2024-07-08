/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:01:04 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:29:39 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_num);
	write_status(LEFT_FORK, philo);
	while (!sim_finished(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

static int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (0);
	elapsed = gettime(MSEC) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (1);
	return (0);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_num, table->philo_num))
		;
	while (!sim_finished(table))
	{
		i = -1;
		while (++i < table->philo_num && !sim_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_int(&table->table_mutex, &table->end_sim, 1);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}

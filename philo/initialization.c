/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:32:34 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:29:18 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_num;

	philo_num = philo->table->philo_num;
	philo->first_fork = &forks[(philo_position + 1) % philo_num];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_num];
	}
}

static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_counter = 0;
		if (mutex_operation(&philo->philo_mutex, INIT) == -1)
			return (-1);
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
	return (0);
}

int	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = 0;
	table->all_threads_ready = 0;
	table->threads_running_num = 0;
	table->philos = s_malloc(table->philo_num * sizeof(t_philo));
	if (table->philos == NULL)
		return (-1);
	table->forks = s_malloc(table->philo_num * sizeof(t_fork));
	if (table->forks == NULL)
		return (-1);
	if (mutex_operation(&table->write_mutex, INIT) == -1)
		return (-1);
	if (mutex_operation(&table->table_mutex, INIT) == -1)
		return (-1);
	while (++i < table->philo_num)
	{
		if (mutex_operation(&table->forks[i].fork, INIT) == -1)
			return (-1);
		table->forks[i].fork_id = i;
	}
	if (philo_init(table) == -1)
		return (-1);
	return (0);
}

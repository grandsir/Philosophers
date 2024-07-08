/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:07:22 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:46:53 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	while (!get_int(&table->table_mutex, &table->all_threads_ready))
		;
}

void	increase_long(t_mtx *mutex, long *value)
{
	mutex_operation(mutex, LOCK);
	(*value)++;
	mutex_operation(mutex, UNLOCK);
}

int	all_threads_running(t_mtx *mutex, long *threads, long philo_num)
{
	int	ret;

	ret = 0;
	mutex_operation(mutex, LOCK);
	if (*threads == philo_num)
		ret = 1;
	mutex_operation(mutex, UNLOCK);
	return (ret);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_num % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, 1);
	}
}

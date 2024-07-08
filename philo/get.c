/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:04:24 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:31:41 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_int(t_mtx *mutex, int *dest, int value)
{
	if (mutex_operation(mutex, LOCK) == -1)
		return (-1);
	*dest = value;
	if (mutex_operation(mutex, UNLOCK) == -1)
		return (-1);
	return (0);
}

int	get_int(t_mtx *mutex, int *value)
{
	int	ret;

	mutex_operation(mutex, LOCK);
	ret = *value;
	mutex_operation(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	mutex_operation(mutex, LOCK);
	ret = *value;
	mutex_operation(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_operation(mutex, LOCK);
	*dest = value;
	mutex_operation(mutex, UNLOCK);
}

int	sim_finished(t_table *table)
{
	return (get_int(&table->table_mutex, &table->end_sim));
}

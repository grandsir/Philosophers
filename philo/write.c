/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:09:37 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:29:18 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <time.h>

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MSEC) - philo->table->start_sim;
	if (philo->full)
		return ;
	mutex_operation(&philo->table->write_mutex, LOCK);
	if (!sim_finished(philo->table))
	{
		if (status == LEFT_FORK || status == RIGHT_FORK)
			printf("%-6ld %d has taken a fork.\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating.\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping.\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking.\n", elapsed, philo->id);
	}
	else if (status == DIED)
		printf("%-6ld %d died.\n", elapsed, philo->id);
	mutex_operation(&philo->table->write_mutex, UNLOCK);
}

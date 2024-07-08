/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:21:27 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:29:39 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, int pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		write_status(THINKING, philo);
	if (philo->table->philo_num % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

static void	eat(t_philo *philo)
{
	mutex_operation(&philo->first_fork->fork, LOCK);
	write_status(LEFT_FORK, philo);
	mutex_operation(&philo->second_fork->fork, LOCK);
	write_status(RIGHT_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->num_limit_meals > 0
		&& philo->meals_counter == philo->table->num_limit_meals)
		set_int(&philo->philo_mutex, &philo->full, 1);
	mutex_operation(&philo->first_fork->fork, UNLOCK);
	mutex_operation(&philo->second_fork->fork, UNLOCK);
}

static void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_num);
	de_synchronize_philos(philo);
	while (!sim_finished(philo->table))
	{
		if (get_int(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, 0);
	}
	return (NULL);
}

static int	dinner_start2(t_table *table, int i)
{
	if (s_thread_handle(&table->monitor, monitor_dinner, table, CREATE) == -1)
		return (-1);
	table->start_sim = gettime(MSEC);
	if (table->start_sim == -1)
		return (-1);
	if (set_int(&table->table_mutex, &table->all_threads_ready, 1) == -1)
		return (-1);
	i = -1;
	while (++i < table->philo_num)
		if (s_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN)
			== -1)
			return (-1);
	if (set_int(&table->table_mutex, &table->end_sim, 1) == -1)
		return (-1);
	if (s_thread_handle(&table->monitor, NULL, NULL, JOIN) == -1)
		return (-1);
	return (0);
}

int	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_limit_meals == 0)
		return (0);
	else if (table->philo_num == 1)
	{
		if (s_thread_handle(&table->philos[0].thread_id, lone_philo,
				&table->philos[0], CREATE) == -1)
			return (-1);
	}
	else
		while (++i < table->philo_num)
			if (s_thread_handle(&table->philos[i].thread_id, dinner_sim,
					&table->philos[i], CREATE) == -1)
				return (-1);
	return (dinner_start2(table, i));
}

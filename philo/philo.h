/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:04:24 by databey           #+#    #+#             */
/*   Updated: 2024/07/08 16:29:39 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	LEFT_FORK,
	RIGHT_FORK,
	DIED,
}						t_philo_status;

typedef enum e_time_code
{
	SECONDS,
	MSEC,
	USEC,
}						t_time_code;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;
typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					full;
	long				meals_counter;
	long				last_meal_time;
	pthread_t			thread_id;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_limit_meals;
	long				philo_num;
	long				start_sim;
	int					end_sim;
	int					all_threads_ready;
	long				threads_running_num;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
};

time_t					gettime(int time_code);
int						parse_input(t_table *table, char **av);
int						s_thread_handle(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode opcode);
int						mutex_operation(t_mtx *mutex, t_opcode opcode);
int						data_init(t_table *table);
int						dinner_start(t_table *table);
int						set_int(t_mtx *mutex, int *dest, int value);
int						get_int(t_mtx *mutex, int *value);
int						sim_finished(t_table *table);
int						error_exit(const char *error);
int						all_threads_running(t_mtx *mutex, long *threads,
							long philo_num);
long					get_long(t_mtx *mutex, long *value);
void					*s_malloc(size_t bytes);
void					set_long(t_mtx *mutex, long *dest, long value);
void					precise_usleep(long usec, t_table *table);
void					clean(t_table *table);
void					write_status(t_philo_status status, t_philo *philo);
void					wait_threads(t_table *table);
void					increase_long(t_mtx *mutex, long *value);
void					thinking(t_philo *philo, int pre_sim);
void					de_synchronize_philos(t_philo *philo);

void					*monitor_dinner(void *data);
void					*lone_philo(void *arg);

#endif

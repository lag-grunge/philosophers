#include "philo.h"

void * ft_process(void *args)
{
	t_philo	*philo;
	int i;

	philo = args;
	usleep(EVEN_LAG);
	i = 0;
	while (1)
	{
		philo->rules->actions[i % 5](philo);
		i++;
	}
	return (NULL);
}

void	dinner_start(t_dinner *dinner)
{
	int			i;
	pthread_t		time_ctrl;

	i = 0;
	get_cur_time(&dinner->rules, 1);
	while (i < dinner->philo_num)
	{
		dinner->philos[i].last_eat_start = 0;
		if (pthread_create(&dinner->philos[i].thread_id, NULL, ft_process, &dinner->philos[i]))
		{
			free(dinner->philos);
			free(dinner->forks);
			exit(pthread_create_error);
		}
		pthread_detach(dinner->philos[i].thread_id);
		i++;
	}
	usleep(WAITER_LAG);
	pthread_create(&time_ctrl, NULL, waiter, dinner);
	dinner->rules.time_ctrl = time_ctrl;
}

void stop_dinner(t_dinner *dinner)
{
	pthread_join(dinner->rules.time_ctrl, NULL);
	pthread_mutex_destroy(dinner->rules.dashboard);
	free(dinner->rules.dashboard);
	pthread_mutex_destroy(dinner->forks);
	free(dinner->forks);
}

void *waiter(void *args)
{
	t_dinner 	*dinner;
	int			i;
	int 		timestamp;

	dinner = args;
	while (!(&dinner->rules)->someone_dead)
	{
		usleep(WAITER_PERIOD);
		i = 0;
		while (i < dinner->philo_num)
		{
			timestamp = get_cur_time((&dinner->rules), 0);
			if ((&dinner->rules)->time_to_die < \
				 timestamp - dinner->philos[i].last_eat_start)
				 {
				(&dinner->rules)->someone_dead = 1;
				display_message(timestamp, dinner->philos + i, die);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

#include "philo_bonus.h"

void * ft_process(void *args)
{
	t_philo	*philo;
	int i;

	philo = args;
	i = 0;
	while (is_living(philo))
	{
		philo->rules->actions[i % 5](philo);
		i++;
	}
	return (NULL);
}

void	dinner_start(t_dinner *dinner)
{
	t_philo 	*philos;
	t_rules		rules;
	int			i;
	int 		timestamp;
//	pthread_t		time_ctrl;

	i = 0;
	get_cur_time(&dinner->rules, 1);
	while (i < dinner->philo_num)
	{
		dinner->philos[i].last_eat_start = get_cur_time(&dinner->rules, 0);
		if (pthread_create(&dinner->philos[i].thread_id, NULL, ft_process, &dinner->philos[i]))
		{
			free(dinner->philos);
			free(dinner->forks);
			exit(pthread_create_error);
		}
		i++;
	}
//	pthread_create(&time_ctrl, NULL, timer, dinner);
//	dinner->rules.time_ctrl = time_ctrl;

//	dinner = args;
	philos = dinner->philos;
	rules = dinner->rules;
	while (1)
	{
		i = 0;
		timestamp = get_cur_time(&rules, 0);
		while (i < dinner->philo_num)
		{
			if (rules.time_to_die <= \
				 timestamp - philos[i].last_eat_start)
				{
					rules.someone_dead = 1;
					display_message(timestamp, philos + i, die);
				}
			i++;
		}
		usleep(TIMEDELAY_NS);
	}
}

void stop_dinner(t_dinner *dinner, int started_threads)
{
	int	i;
	i = started_threads;
	while (i > 0)
	{
		pthread_join(dinner->philos[i - 1].thread_id, NULL);
		i--;
	}
	pthread_join(dinner->rules.time_ctrl, NULL);
}

void *timer(void *args)
{
	t_dinner 	*dinner;
	t_philo 	*philos;
	t_rules		rules;
	int			i;
	int 		timestamp;

	dinner = args;
	philos = dinner->philos;
	rules = dinner->rules;
	i = 0;
	while (1)
	{
		while (i < dinner->philo_num)
		{
			timestamp = get_cur_time(&rules, 0);
			if (rules.time_to_die <= \
				 timestamp - philos[i].last_eat_start)
				{
					rules.someone_dead = 1;
					display_message(timestamp, philos + i, die);
				}
			i++;
		}
		usleep(TIMEDELAY_NS);
	}
	return (NULL);
}

#include "philo.h"

void * ft_process(void *args)
{
	t_philo	*philo;
	int i;

	philo = args;
	i = 0;
	while (is_living(philo))
	{
		philo->rules->actions[i % 4](philo);
		i++;
	}
	display_message(get_cur_time(philo->rules, 0), philo, die);
	philo->rules->someone_dead = 1;
	return (NULL);
}


void	dinner_start(t_dinner *dinner)
{
	int	i;

	i = 0;
	get_cur_time(&dinner->rules, 1);
	while (i < dinner->philo_num)
	{
		if (pthread_create(&dinner->philos[i].thread_id, NULL, ft_process, &dinner->philos[i]))
		{
			free(dinner->philos);
			free(dinner->forks);
			exit(pthread_create_error);
		}
		i++;
	}
}

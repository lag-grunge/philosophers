#include "philo.h"

void * ft_process(void *args)
{
	t_philo	*philo;
	t_rules *rules;
	int 	ret;

	philo = args;
	rules = philo->rules;
	ret = !pthread_mutex_lock(philo->l_fork) && !pthread_mutex_lock(philo->r_fork);
	while (ret && rules->time_to_die > get_cur_time() - philo->last_eat_start)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		ret = !pthread_mutex_lock(philo->l_fork) && !pthread_mutex_lock(philo->r_fork);

	}
	if (!ret)
		exit (mutex_lock_error);
	else
		display_message(get_cur_time(), )



}

void	dinner_start(t_dinner *dinner)
{
	int	i;

	i = 0;
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

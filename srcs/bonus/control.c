#include "../../includes/philo_bonus.h"

void * ft_process(void *args)
{
	t_philo	*philo;
	int i;

	philo = args;
	display_message(EVEN_LAG, philo, tmst);
	usleep(EVEN_LAG);
	i = 0;
	while (!stop(philo))
	{
		philo->rules->actions[i % ACTIONS_NUM](philo);
		if (i % ACTIONS_NUM == eat)
			philo->eat_num++;
		i++;
	}
	usleep(WAITER_PERIOD);
	sem_post(philo->rules->stop_die);
	exit (0);
}

void	dinner_start(t_dinner *dinner)
{
	int			i;
	pthread_t	time_ctrl;

	get_cur_time(&dinner->rules, 1);
	i = 0;
	while (i < dinner->philo_num)
	{
		dinner->philos[i].last_eat_start = 0;
		dinner->philos[i].pid = fork();
		if (dinner->philos[i].pid < 0)
		{
			free(dinner->philos);
			exit(fork_create_error);
		}
		else if (dinner->philos[i].pid == 0)
			ft_process(dinner->philos + i);
		else
			i++;
	}
	if (dinner->rules.stop_lim)
	{
		pthread_create(&time_ctrl, NULL, waiter_lim, dinner);
		pthread_detach(time_ctrl);
	}
	pthread_create(&time_ctrl, NULL, waiter_die, dinner);
	pthread_detach(time_ctrl);
}

void stop_dinner(t_dinner *dinner)
{
	int i;

	i = dinner->philo_num;
	while (i > 0)
	{
		waitpid(-1, NULL, 0);
		i--;
	}
	sem_close(dinner->rules.dashboard);
	sem_close(dinner->forks);
	sem_close(dinner->rules.stop_die);
	sem_unlink("dashboard");
	sem_unlink("forks");
	sem_unlink("stop_die");
	if (dinner->rules.stop_lim)
	{
		sem_close(dinner->rules.stop_lim);
		sem_unlink("stop_lim");
	}
}

void *waiter_die(void *args)
{
	t_dinner 	*dinner;
	int			i;
	int 		timestamp;

	dinner = args;
	usleep(WAITER_DIE_LAG);
	while (1)
	{
		usleep(WAITER_PERIOD);
		while (1)
		{
			timestamp = get_cur_time(&dinner->rules, 0);
			sem_wait(dinner->rules.stop_die);
			sem_post(dinner->rules.stop_die);
			if (get_cur_time(&dinner->rules, 0) - timestamp >= \
					1000)
			{
				i = 0;
				while (i < dinner->philo_num)
				{
					kill(dinner->philos[i].pid, SIGKILL);
					i++;
				}
				return (NULL);
			}
		}
	}
	return (NULL);
}

void *waiter_lim(void *args)
{
	t_dinner 	*dinner;
	int			i;
	int 		timestamp;

	dinner = args;
	usleep(WAITER_LIM_LAG);
	while (1)
	{
		usleep(1000);
		timestamp = get_cur_time(&dinner->rules, 0);
		sem_wait(dinner->rules.stop_lim);
		sem_post(dinner->rules.stop_lim);
		if (get_cur_time(&dinner->rules, 0) - timestamp >= \
				WAITER_PERIOD)
		{
			display_message(timestamp, dinner->philos, lim);
			i = 0;
			while (i < dinner->philo_num)
			{
				kill(dinner->philos[i].pid, SIGKILL);
				i++;
			}
		}
	}
	return (NULL);
}


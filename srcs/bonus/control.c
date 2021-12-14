#include "../../includes/philo_bonus.h"

void * ft_process(void *args)
{
	t_philo	*philo;
	int i;

	philo = args;
	u_sleep(EVEN_LAG);
	i = 0;
	while (!stop_die(philo))
	{
		philo->rules->actions[i % ACTIONS_NUM](philo);
		if (i % ACTIONS_NUM == eat)
		{
			philo->eat_num++;	
			if (philo->rules->limit_eats > -1  && \
				philo->eat_num == philo->rules->limit_eats)
				sem_post(philo->rules->stop_lim);
		}
		i++;
	}
	u_sleep(SIGNAL_DIE);
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
	u_sleep(WAITER_DIE_LAG);
	while (1)
	{
		while (1)
		{
			timestamp = get_cur_time(&dinner->rules, 0);
			sem_wait(dinner->rules.stop_die);
			sem_post(dinner->rules.stop_die);
			if (get_cur_time(&dinner->rules, 0) - timestamp >= \
					MIN_TIME)
			{
				i = 0;
				while (i < dinner->philo_num)
				{
					kill(dinner->philos[i].pid, SIGKILL);
					i++;
				}
				return (NULL);
			}
			u_sleep(MIN_TIME);
		}
	}
	return (NULL);
}

void *waiter_lim(void *args)
{
	t_dinner 	*dinner;
	int			i;
	int 		ret;

	dinner = args;
	u_sleep(WAITER_LIM_LAG);
	i = 0;
	while (i < dinner->philo_num)
	{
		ret = sem_wait(dinner->rules.stop_lim);
		if (!ret)
			i++;
		else
			perror("waiter_lim");
	}
	display_message(get_cur_time(&dinner->rules, 0), dinner->philos, lim);
	kill(0, SIGTERM);
			//i = 0;
			// while (i < dinner->philo_num)
			//{
			//	kill(dinner->philos[i].pid, SIGTERM);
			//	i++;
			//}
	return (NULL);
}


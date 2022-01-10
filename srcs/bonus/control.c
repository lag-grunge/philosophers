/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:26:24 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/11 01:33:34 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	*ft_process(void *args)
{
	pthread_t	time_ctrl;
	t_philo		*philo;

	philo = args;
	philo->last_eat_start = 0;
	if (philo->rules->limit_eats == 0)
	{
		sem_post(philo->rules->lim_stop);
		exit(0);
	}
	u_sleep((philo->id % 2 == 0) * EVEN_LAG);
	pthread_create(&time_ctrl, NULL, waiter_die, philo);
	pthread_detach(time_ctrl);
	while (1)
	{
		trying_forks(philo);
		eating(philo);
		philo->eat_num++;
		if (philo->rules->limit_eats > -1 && \
			philo->eat_num == philo->rules->limit_eats)
			sem_post(philo->rules->lim_stop);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_dinner *dinner)
{
	pthread_t	time_ctrl;
	int			i;

	i = 0;
	gettimeofday(&dinner->rules.start_time, NULL);
	while (i < dinner->philo_num)
	{
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
	if (dinner->rules.limit_eats > -1)
	{
		pthread_create(&time_ctrl, NULL, waiter_lim, dinner);
		pthread_detach(time_ctrl);
	}
}

void	stop_dinner(t_dinner *dinner)
{
	sem_wait(dinner->rules.stop_die);
	kill_em(dinner);
	sem_close(dinner->forks);
	sem_unlink("forks");
	sem_close(dinner->rules.stop_die);
	sem_unlink("stop_die");
	sem_close(dinner->rules.dashboard);
	sem_unlink("dashboard");
	free(dinner->philos);
	if (dinner->rules.lim_stop)
	{
		sem_close(dinner->rules.lim_stop);
		sem_unlink("lim_stop");
	}
	if (dinner->philo_num % 2)
	{
		sem_close(dinner->rules.next);
		sem_unlink("next");
	}
	free(dinner);
}

void	*waiter_die(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	u_sleep(philo->rules->time_to_die * 1000);
	while (1)
	{
		timestamp = get_cur_time(philo->rules);
		if (philo->rules->time_to_die < \
		timestamp - philo->last_eat_start)
		{
			sem_wait(philo->rules->dashboard);
			printf("%d %d died\n", timestamp, philo->id);
			sem_post(philo->rules->stop_die);
			exit (0);
		}
		u_sleep(WAITER_PERIOD);
	}
}

void	*waiter_lim(void *args)
{
	t_dinner	*dinner;
	int			i;

	dinner = args;
	i = 0;
	while (i < dinner->philo_num)
	{
		sem_wait(dinner->rules.lim_stop);
		i++;
	}
	sem_wait(dinner->rules.dashboard);
	printf("%d philosophers has eaten at least %d\n", \
			get_cur_time(&dinner->rules), dinner->rules.limit_eats);
	sem_post(dinner->rules.stop_die);
	return (NULL);
}

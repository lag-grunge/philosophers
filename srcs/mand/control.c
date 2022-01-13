/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:45:09 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 10:16:34 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*ft_process(void *args)
{
	t_philo		*philo;
	int			(*func[4])(void *);
	int			i;

	philo = args;
	while (!philo->rules->start_time.tv_sec)
		usleep(10);
	if (philo->rules->started_philos < philo->rules->philo_num)
		return (NULL);
	u_sleep((philo->id % 2 == 0 || philo->last) * EVEN_LAG);
	func[0] = trying_forks;
	func[1] = eating;
	func[2] = sleeping;
	func[3] = thinking;
	i = 0;
	while (!philo->rules->stop && !func[i++ % 4](philo))
		;
	pthread_mutex_unlock(&philo->rules->eat_mut \
	[left_id(philo, philo->id) - 1]);
	pthread_mutex_unlock(&philo->rules->eat_mut \
	[right_id(philo, philo->id) - 1]);
	pthread_mutex_unlock(philo->rules->state_mut);
	pthread_mutex_unlock(philo->rules->dashboard);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (NULL);
}

void	dinner_start(t_dinner *dinner)
{
	pthread_t	time_ctrl;
	int			i;

	i = 0;
	while (i < dinner->philo_num)
	{
		if (pthread_create(&dinner->philos[i].thread_id, \
					NULL, ft_process, &dinner->philos[i]))
			break ;
		i++;
	}
	dinner->rules.started_philos = i;
	gettimeofday(&dinner->rules.start_time, NULL);
	if (i < dinner->philo_num)
		return ;
	if (dinner->rules.limit_eats > -1)
	{
		pthread_create(&time_ctrl, NULL, waiter_lim, dinner);
		pthread_detach(time_ctrl);
	}
	u_sleep(WAITER_LAG);
	pthread_create(&time_ctrl, NULL, waiter_die, dinner);
	dinner->rules.time_ctrl = time_ctrl;
}

void	stop_dinner(t_dinner *dinner)
{
	int	i;

	if (dinner->rules.time_ctrl)
		pthread_join(dinner->rules.time_ctrl, NULL);
	i = dinner->rules.started_philos;
	while (i)
	{
		pthread_join(dinner->philos[i - 1].thread_id, NULL);
		i--;
	}
	pthread_mutex_destroy(dinner->rules.dashboard);
	free(dinner->rules.dashboard);
	pthread_mutex_destroy(dinner->forks);
	free(dinner->forks);
	if (dinner->rules.time_ctrl)
		free(dinner->philos);
	free(dinner->rules.states);
	pthread_mutex_destroy(dinner->rules.eat_mut);
	free(dinner->rules.eat_mut);
	pthread_mutex_destroy(dinner->rules.state_mut);
	free(dinner->rules.state_mut);
}

void	*waiter_lim(void *args)
{
	t_dinner	*dinner;
	int			i;

	dinner = args;
	while (!dinner->rules.stop)
	{
		u_sleep(WAITER_PERIOD);
		i = 0;
		while (i < dinner->philo_num)
		{
			if (dinner->rules.limit_eats > dinner->philos[i].eat_num)
				break ;
			i++;
		}
		if (i == dinner->philo_num && !dinner->rules.stop)
		{
			dinner->rules.stop = 1;
			pthread_mutex_lock(dinner->rules.dashboard);
			printf("%d philosophers has eaten at least %d\n", \
					get_cur_time(&dinner->rules), dinner->rules.limit_eats);
		}
	}
	return (NULL);
}

void	*waiter_die(void *args)
{
	t_dinner	*dinner;
	int			i;
	int			timestamp;

	dinner = args;
	while (!dinner->rules.stop)
	{
		u_sleep(WAITER_PERIOD);
		i = 0;
		while (i < dinner->philo_num)
		{
			timestamp = get_cur_time(&dinner->rules);
			if (dinner->rules.time_to_die < \
				timestamp - dinner->philos[i].last_eat_start)
				break ;
			i++;
		}
		if (i < dinner->philo_num && !dinner->rules.stop)
		{
			dinner->rules.stop = 1;
			pthread_mutex_lock(dinner->rules.dashboard);
			printf("%d %d died\n", timestamp, i + 1);
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 03:19:02 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 03:25:41 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static void	*actions(void *args)
{
	t_philo	*philo;
	int		(*func[4])(void *);
	int		(*cur_action)(void *);
	int		i;

	philo = args;
	u_sleep((philo->id % 2 == 0) * EVEN_LAG);
	func[0] = trying_forks;
	func[1] = eating;
	func[2] = sleeping;
	func[3] = thinking;
	i = 0;
	cur_action = trying_forks;
	while (!cur_action(philo))
	{
		i++;
		i %= 4;
		cur_action = func[i];
	}
	return (NULL);
}

static void	*waiter_die(void *args)
{
	t_philo	*philo;
	int		timestamp;
	int		i;

	philo = args;
	u_sleep(philo->rules->time_to_die * 1000);
	while (!philo->stop)
	{
		timestamp = get_cur_time(philo->rules);
		if (philo->rules->time_to_die < \
		timestamp - philo->last_eat_start)
		{
			philo->stop = 1;
			sem_wait(philo->rules->dashboard);
			printf("%d %d died\n", timestamp, philo->id);
			if (philo->rules->eat_ctrl)
				kill(philo->rules->eat_ctrl, SIGKILL);
			i = -1;
			while (++i < philo->philo_num)
				sem_post(philo->rules->stop_die);
			return (NULL);
		}
		usleep(WAITER_PERIOD);
	}
	return (NULL);
}

static void	*stop(void *args)
{
	t_philo		*philo;

	philo = args;
	sem_wait(philo->rules->stop_die);
	philo->stop = 1;
	return (NULL);
}

static void	start_thread(pthread_t *th, void *(*func)(void *), t_philo *philo)
{
	if (pthread_create(th, NULL, func, (void *) philo))
	{
		sem_post(philo->rules->stop_die);
		if (philo->rules->eat_ctrl)
			kill(philo->rules->eat_ctrl, SIGKILL);
		exit(pthread_create_error);
	}
}

void	*ft_process(void *args)
{
	pthread_t	ctrl[3];
	t_philo		*philo;

	philo = args;
	if (philo->rules->limit_eats == 0)
		sem_post(philo->rules->lim_stop);
	if (philo->rules->limit_eats == 0)
		exit(0);
	start_thread(&ctrl[0], waiter_die, philo);
	start_thread(&ctrl[1], actions, philo);
	start_thread(&ctrl[2], stop, philo);
	pthread_join(ctrl[2], NULL);
	pthread_join(ctrl[1], NULL);
	pthread_join(ctrl[0], NULL);
	return (NULL);
}

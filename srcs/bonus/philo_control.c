/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 03:19:02 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 10:13:23 by sdalton          ###   ########.fr       */
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
	while (!philo->stop && !cur_action(philo))
	{
		i++;
		i %= 4;
		cur_action = func[i];
	}
	return (NULL);
}

static void	*waiter_die(void *args)
{
	t_philo			*philo;
	int				timestamp;

	philo = args;
	u_sleep((philo->rules->time_to_die - 1) * 1000);
	while (!philo->stop)
	{
		timestamp = get_cur_time(philo->rules);
		if (philo->rules->time_to_die < \
		timestamp - philo->last_eat_start)
		{
			sem_wait(philo->rules->dashboard);
			if (philo->stop)
				return (NULL);
			death_philo_operations(philo, timestamp);
		}
		usleep(100);
	}
	return (NULL);
}

static void	*stop_threads(void *args)
{
	t_philo		*philo;

	philo = args;
	sem_wait(philo->rules->stop_die);
	philo->stop = 1;
	usleep(1000 * 1000);
	sem_post(philo->rules->dashboard);
	sem_post(philo->rules->next);
	sem_post(philo->forks);
	return (NULL);
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
	start_thread(&ctrl[2], stop_threads, philo);
	pthread_join(ctrl[2], NULL);
	pthread_join(ctrl[1], NULL);
	pthread_join(ctrl[0], NULL);
	return (NULL);
}

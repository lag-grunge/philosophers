/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:18:59 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/11 01:23:42 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	eating(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	philo->last_eat_start = timestamp;
	sem_wait(philo->rules->dashboard);
	if (philo->stop)
		return (1);
	printf("%d %d is eating\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_eat * 1000);
	sem_post(philo->forks);
	sem_post(philo->forks);
	sem_post(philo->rules->next);
	philo->eat_num++;
	if (philo->rules->limit_eats > -1 && \
			philo->eat_num == philo->rules->limit_eats)
		sem_post(philo->rules->lim_stop);
	return (0);
}

int	sleeping(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	if (philo->stop)
		return (1);
	printf("%d %d is sleeping\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_sleep * 1000);
	return (0);
}

static int	get_fork(t_philo *philo)
{
	int	timestamp;

	if (philo->stop)
		return (1);
	sem_wait(philo->forks);
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	if (philo->stop)
		return (1);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	return (0);
}

int	trying_forks(void *args)
{
	t_philo	*philo;

	philo = args;
	sem_wait(philo->rules->next);
	if (get_fork(philo))
		return (1);
	if (philo->stop || philo->philo_num == 1)
		return (1);
	if (get_fork(philo))
		return (1);
	return (0);
}

int	thinking(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	if (philo->stop)
		return (1);
	printf("%d %d is thinking\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:00:53 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 10:14:44 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	eating(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	philo->last_eat_start = timestamp;
	pthread_mutex_lock(philo->rules->dashboard);
	if (philo->rules->stop)
		return (1);
	printf("%d %d is eating\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_eat * 1000);
	philo->eat_num++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->rules->stop)
		return (1);
	pthread_mutex_lock(philo->rules->state_mut);
	philo->rules->states[philo->id - 1] = thnk;
	test(left_philo(philo, philo->id));
	usleep(philo->rules->philo_num % 2 * 100);
	test(right_philo(philo, philo->id));
	pthread_mutex_unlock(philo->rules->state_mut);
	return (0);
}

int	sleeping(void *args)
{
	t_philo	*philo;

	philo = args;
	pthread_mutex_lock(philo->rules->dashboard);
	if (philo->rules->stop)
		return (1);
	printf("%d %d is sleeping\n", get_cur_time(philo->rules), philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_sleep * 1000);
	return (0);
}

static int	get_fork(t_philo *philo, int left)
{
	int	timestamp;

	if (left)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	timestamp = get_cur_time(philo->rules);
	pthread_mutex_lock(philo->rules->dashboard);
	if (philo->rules->stop)
		return (1);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	return (0);
}

int	trying_forks(void *args)
{
	t_philo	*philo;

	philo = args;
	pthread_mutex_lock(philo->rules->state_mut);
	philo->rules->states[philo->id - 1] = frk1;
	test(philo);
	pthread_mutex_unlock(philo->rules->state_mut);
	if (philo->rules->stop)
		return (1);
	pthread_mutex_lock(&philo->rules->eat_mut[philo->id - 1]);
	if (philo->rules->stop)
		return (1);
	if (get_fork(philo, 1))
		return (1);
	if (philo->r_fork == philo->l_fork || philo->rules->stop)
		return (1);
	if (get_fork(philo, 0))
		return (1);
	return (0);
}

int	thinking(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	pthread_mutex_lock(philo->rules->dashboard);
	if (philo->rules->stop)
		return (1);
	printf("%d %d is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	return (0);
}

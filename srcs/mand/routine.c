/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:00:53 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/02 11:44:39 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(void *args)
{
	int timestamp;
	t_philo *philo;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	philo->last_eat_start = timestamp;
	pthread_mutex_lock(philo->rules->dashboard);
	printf("%d %d is eating\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void sleeping(void *args)
{
	t_philo *philo;

	philo = args;
	pthread_mutex_lock(philo->rules->dashboard);
	printf("%d %d is sleeping\n", get_cur_time(philo->rules), philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_sleep * 1000);
}

void trying_forks(void *args)
{
	t_philo *philo;
	int	timestamp;

	philo = args;
/*	if (philo->id % 2 == 0 || philo->last)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->rules->dashboard);
		printf("%d %d has taken a fork\n", get_cur_time(philo->rules), philo->id);
		pthread_mutex_unlock(philo->rules->dashboard);
		pthread_mutex_lock(philo->l_fork);
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->rules->dashboard);
		printf("%d %d has taken a fork\n", get_cur_time(philo->rules), philo->id);
		pthread_mutex_unlock(philo->rules->dashboard);
		pthread_mutex_lock(philo->r_fork);
	}*/
	pthread_mutex_lock(philo->l_fork);
	timestamp = get_cur_time(philo->rules);
	pthread_mutex_lock(philo->rules->dashboard);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	pthread_mutex_lock(philo->r_fork);
	timestamp = get_cur_time(philo->rules);
	pthread_mutex_lock(philo->rules->dashboard);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
}

void thinking(void *args)
{
	t_philo *philo;
	int timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	pthread_mutex_lock(philo->rules->dashboard);
	printf("%d %d is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->dashboard);
	if (philo->thinker && \
			philo->rules->time_to_eat >= philo->rules->time_to_sleep)
	{
		if (philo->rules->time_to_sleep < philo->rules->time_to_eat)
			u_sleep((philo->rules->time_to_eat - philo->rules->time_to_sleep) * 1000);
		u_sleep(THIRD_GROUP_LAG);
	}
}
/*
*/

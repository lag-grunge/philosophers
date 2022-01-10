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

void	eating(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	philo->last_eat_start = timestamp;
	sem_wait(philo->rules->dashboard);
	printf("%d %d is eating\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_eat * 1000);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	sleeping(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	printf("%d %d is sleeping\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_sleep * 1000);
}

void	trying_forks(void *args)
{
	t_philo	*philo;
	int		timestamp;

	philo = args;
	sem_wait(philo->rules->next);
	sem_wait(philo->forks);
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	sem_wait(philo->forks);
	sem_post(philo->rules->next);
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
}

void	thinking(void *args)
{
	t_philo	*philo;
	int		timestamp;
	int		more;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	printf("%d %d is thinking\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	more = (philo->rules->time_to_eat - philo->rules->time_to_sleep);
	if (philo->thinker && more >= 0)
	{
		if (more > 0)
			u_sleep(more * 1000);
		u_sleep(THIRD_GROUP_LAG);
	}
}

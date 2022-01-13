/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 08:05:51 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 08:05:53 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_thread(pthread_t *th, void *(*func)(void *), t_philo *philo)
{
	if (pthread_create(th, NULL, func, (void *) philo))
	{
		sem_post(philo->rules->stop_die);
		if (philo->rules->eat_ctrl)
			kill(philo->rules->eat_ctrl, SIGKILL);
		exit(pthread_create_error);
	}
}

void	death_philo_operations(t_philo *philo, int timestamp)
{
	int	i;

	philo->stop = 1;
	printf("%d %d died\n", timestamp, philo->id);
	i = -1;
	while (++i < philo->philo_num + 2)
		sem_post(philo->rules->stop_die);
	if (philo->rules->eat_ctrl)
		kill(philo->rules->eat_ctrl, SIGKILL);
}

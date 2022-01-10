/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 02:16:39 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/11 02:19:06 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	left_id(t_philo *philo, int i)
{
	int	philo_num;

	philo_num = philo->rules->philo_num;
	i -= 1;
	if (i == 0)
		return (philo_num);
	return (i);
}

t_philo	*left_philo(t_philo *philo, int i)
{
	int	philo_num;

	philo_num = philo->rules->philo_num;
	i -= 1;
	if (i == 0)
		return (philo->rules->philos + philo_num - 1);
	return (philo->rules->philos + i - 1);
}

int	right_id(t_philo *philo, int i)
{
	int	philo_num;

	philo_num = philo->rules->philo_num;
	i += 1;
	if (i > philo_num)
		return (1);
	return (i);
}

t_philo	*right_philo(t_philo *philo, int i)
{
	int	philo_num;

	philo_num = philo->rules->philo_num;
	i += 1;
	if (i > philo_num)
		return (philo->rules->philos);
	return (philo->rules->philos + i - 1);
}

void	test(t_philo *philo)
{
	int	*states;
	int	i;

	states = philo->rules->states;
	i = philo->id;
	if (states[i - 1] == frk1 && \
		states[left_id(philo, i) - 1] != eat && \
		states[right_id(philo, i) - 1] != eat)
	{
		states[i - 1] = eat;
		pthread_mutex_unlock(&philo->rules->eat_mut[i - 1]);
	}
}

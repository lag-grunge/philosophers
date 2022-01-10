/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 02:21:24 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/11 02:32:07 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	init_mutex(pthread_mutex_t **m)
{
	*m = malloc(sizeof(pthread_mutex_t) * 1);
	if (!*m)
		exit(malloc_err);
	pthread_mutex_init(*m, NULL);
}

void	get_rules(t_rules *rules, int philo_num, char *argv[])
{
	pthread_mutex_t	*m;

	rules->stop = 0;
	rules->start_time.tv_sec = 0;
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->philo_num = philo_num;
	rules->states = (int *)malloc(sizeof(int) * philo_num);
	if (!rules->states)
		exit(malloc_err);
	memset((char *)rules->states, 0, sizeof(int) * philo_num);
	rules->limit_eats = -1;
	if (argv[5])
		rules->limit_eats = ft_atoi(argv[5]);
	init_mutex(&m);
	rules->dashboard = m;
	init_mutex(&m);
	rules->state_mut = m;
	init_mutex_arr(&rules->eat_mut, philo_num, 1);
	rules->time_ctrl = 0;
}

void	get_philos(t_philo **philos, int philo_num, t_dinner *dinner)
{
	t_philo	*p;
	int		i;

	p = (t_philo *) malloc(sizeof(t_philo) * philo_num);
	i = 0;
	while (i < philo_num)
	{
		p[i].id = i + 1;
		p[i].rules = &dinner->rules;
		p[i].eat_num = 0;
		p[i].r_fork = &dinner->forks[i];
		p[i].l_fork = &dinner->forks[(i + 1) % philo_num];
		p[i].last = (p[i].id == philo_num);
		p[i].thinker = philo_num % 2;
		p[i].last_eat_start = 0;
		i++;
	}
	*philos = p;
}

void	init_mutex_arr(pthread_mutex_t **mut_arr, int philo_num, int lock)
{
	pthread_mutex_t	*m;
	int				i;

	m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_num);
	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&m[i], NULL);
		i++;
	}
	*mut_arr = m;
	if (!lock)
		return ;
	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_lock(m + i);
		i++;
	}
}

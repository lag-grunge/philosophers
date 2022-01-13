/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:35:04 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/11 01:36:41 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

sem_t	*my_sem_open(char *filename, int value)
{
	sem_t	*s;

	sem_unlink(filename);
	s = sem_open(filename, O_CREAT | O_EXCL, 0666, value);
	if (s == SEM_FAILED)
		exit (3);
	return (s);
}

void	get_rules(t_rules *rules, int philo_num, char *argv[])
{
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->limit_eats = -1;
	if (argv[5])
		rules->limit_eats = ft_atoi(argv[5]);
	rules->stop_die = my_sem_open("stop_die", 0);
	rules->dashboard = my_sem_open("dashboard", 1);
	rules->lim_stop = NULL;
	rules->eat_ctrl = 0;
	if (rules->limit_eats > -1)
		rules->lim_stop = my_sem_open("lim_stop", 0);
	if (philo_num == 1)
		rules->next = my_sem_open("next", 1);
	else
		rules->next = my_sem_open("next", philo_num / 2);
}

void	get_philos(t_philo **philos, int philo_num, t_dinner *dinner)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)malloc(sizeof(t_philo) * philo_num);
	if (!p)
		exit (malloc_error);
	i = 0;
	while (i < philo_num)
	{
		p[i].id = i + 1;
		p[i].rules = &dinner->rules;
		p[i].eat_num = 0;
		p[i].forks = dinner->forks;
		p[i].thinker = philo_num % 2;
		p[i].last_eat_start = 0;
		p[i].stop = 0;
		p[i].philo_num = philo_num;
		i++;
	}
	*philos = p;
}

void	get_forks(sem_t **forks, int argc)
{
	*forks = my_sem_open("forks", argc);
	if (*forks == SEM_FAILED)
		exit (3);
}

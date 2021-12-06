#include "philo_bonus.h"

//	записать правила
void get_rules(t_rules *rules, char *argv[])
{
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->limit_eats = -1;
	rules->stop_lim = NULL;
	if (argv[5])
	{
		rules->limit_eats = ft_atoi(argv[5]);
		rules->stop_lim = sem_open("stop_lim", O_CREAT, 0666, rules->limit_eats);
	}
	rules->stop_die = sem_open("stop_die", O_CREAT, 0666, 1);
	if (rules->stop_die == SEM_FAILED)
		exit (3);
	rules->dashboard = sem_open("dashboard", O_CREAT, 0666, 1);
	if (rules->dashboard == SEM_FAILED)
		exit (3);
	rules->actions[0] = trying_forks;
	rules->actions[1] = trying_forks;
	rules->actions[2] = eating;
	rules->actions[3] = sleeping;
	rules->actions[4] = thinking;
}

void get_philos(t_philo **philos, int philo_num, t_dinner *dinner)
{
	int	i;
	t_philo *p;

	p = (t_philo *) malloc(sizeof(t_philo) * philo_num);
	i = 0;
	while (i < philo_num)
	{
		p[i].id = i + 1;
		p[i].rules = &dinner->rules;
		p[i].eat_num = 0;
		p[i].forks = dinner->forks;
		i++;
	}
	*philos = p;
}

void get_forks(sem_t **forks, int argc)
{
	*forks = sem_open("forks", O_CREAT, 0666, argc);
	if (*forks == SEM_FAILED)
		exit (3);
}

#include "philo.h"

int get_philos_num(char *s)
{
	int num;

	num = ft_atoi(s);
	if (num < 1)
		exit (philo_num_error);
	return (num);
}

//	записать правила
void get_rules(t_rules *rules, char *argv[])
{
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->num_eats = 0;
	if (argv[5])
		rules->limit_eats = ft_atoi(argv[5]);
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
		p[i].last_eat_start = 0;
		p[i].l_fork = &dinner->forks[i];
		p[i].r_fork = &dinner->forks[(i + 1) % philo_num];
		p[i].rules = dinner->rules;
		i++;
	}
	*philos = p;
}

void get_forks(pthread_mutex_t **forks, int argc)
{
	int i;
	pthread_mutex_t *m;

	m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * argc);
	i = 0;
	while (i < argc)
	{
		pthread_mutex_init(&m[i], NULL);
		i++;
	}
	*forks = m;
}

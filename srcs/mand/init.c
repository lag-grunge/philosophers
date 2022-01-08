#include "philo.h"

static void	init_mutex(pthread_mutex_t **m)
{
	*m = malloc(sizeof(pthread_mutex_t) *  1);
	if (!*m)
		exit(malloc_err);
	pthread_mutex_init(*m, NULL);
}

void	get_rules(t_rules *rules, char *argv[])
{
	pthread_mutex_t *m;

	rules->stop = 0;
	rules->start_time.tv_sec = 0;
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->limit_eats = -1;
	if (argv[5])
		rules->limit_eats = ft_atoi(argv[5]);
	init_mutex(&m);
	rules->dashboard = m;
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
		p[i].r_fork = &dinner->forks[i];
		p[i].l_fork = &dinner->forks[(i + 1) % philo_num];
		p[i].last = (p[i].id == philo_num);
		p[i].thinker = philo_num % 2;
		p[i].last_eat_start = 0;
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

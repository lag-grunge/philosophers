#include "philo.h"

void eating(void *args)
{
	int timestamp;
	t_philo *philo;

	philo = args;
	timestamp = get_cur_time(philo->rules, 0);
	philo->last_eat_start = timestamp;
	display_message(timestamp, philo, eat);
	u_sleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void sleeping(void *args)
{
	int timestamp;
	t_philo *philo;

	philo = args;
	timestamp = get_cur_time(philo->rules, 0);
	display_message(timestamp, philo, slp);
	u_sleep(philo->rules->time_to_sleep * 1000);
}

void trying_forks(void *args)
{
	pthread_mutex_t *cur;
	enum e_forks next;
	t_philo *philo;


	philo = args;
	cur = philo->l_fork;
	next = r_fork;
	if (philo->cur_fork == r_fork)
	{
		cur = philo->r_fork;
		next = l_fork;
	}
	pthread_mutex_lock(cur);
	display_message(get_cur_time(philo->rules, 0), philo, frk1);
	philo->cur_fork = next;
}

void thinking(void *args)
{
	t_philo *philo;
	int timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules, 0);
	display_message(timestamp, philo, thnk);
}

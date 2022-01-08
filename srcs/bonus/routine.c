#include "../../includes/philo_bonus.h"

void eating(void *args)
{
	int timestamp;
	t_philo *philo;

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

void sleeping(void *args)
{
	int timestamp;
	t_philo *philo;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	printf("%d %d is sleeping\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	u_sleep(philo->rules->time_to_sleep * 1000);
}

void trying_forks(void *args)
{
	t_philo *philo;
	int	timestamp;

	philo = args;
	if (philo->thinker)
	{
		sem_wait(philo->rules->next);
	}
	sem_wait(philo->forks);
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	sem_wait(philo->forks);
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	printf("%d %d has taken a fork\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
	if (philo->thinker)
	{
		sem_post(philo->rules->next);
	}
}

void thinking(void *args)
{
	t_philo *philo;
	int timestamp;

	philo = args;
	timestamp = get_cur_time(philo->rules);
	sem_wait(philo->rules->dashboard);
	printf("%d %d is thinking\n", timestamp, philo->id);
	sem_post(philo->rules->dashboard);
}

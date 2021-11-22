#include "philo.h"

void display_message(time_t timestamp, t_philo *philo, int msg)
{
	static pthread_mutex_t *m;

	if (!m)
		pthread_mutex_init(m, NULL);
	pthread_mutex_lock(m);
	if (msg == eat)
	{
		printf("%ld %d  eat", timestamp, philo->id);
	}
	else if (msg == slp)
	{
		printf("%ld %d  sleep", timestamp, philo->id);
	}
	else if (msg == thnk)
	{
		printf("%ld %d  thinks", timestamp, philo->id);
	}
	else if (msg == die)
	{
		printf("%ld %d  dies", timestamp, philo->id);
	}
	pthread_mutex_unlock(m);
}


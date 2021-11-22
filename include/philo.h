#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

enum errors {
	philo_num_error = 1,
	pthread_create_error = 2,
	mutex_lock_error = 3
};

enum msgs {
	eat = 0,
	slp = 1,
	thnk = 2,
	die = 3
};

typedef struct s_rules {
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	size_t	num_eats;
	size_t	limit_eats;
}				t_rules;

typedef struct s_philo {
	int 			id;
	pthread_t		thread_id;
	time_t			last_eat_start;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	t_rules			*rules;
}				t_philo;

typedef struct s_dinner {
	t_philo 		*philos;
	int 			philo_num;
	pthread_mutex_t *forks;
	t_rules			*rules;
}				t_dinner;


int get_philos_num(char *s);
void get_rules(t_rules *rules, char *argv[]);
void get_philos(t_philo **philos, int philo_num, t_dinner *dinner);
void get_forks(pthread_mutex_t **forks, int argc);

void * ft_process(void *args);
void	dinner_start(t_dinner *dinner);
void	stop_dinner(t_dinner *dinner, int started_threads);

time_t	get_cur_time();
time_t	get_interval();

void eating(t_philo *philo);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);

void display_message(time_t timestamp, t_philo *philo, int msg);

#endif

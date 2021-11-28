#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# define ARG_ERROR "Usage: ./philo number_of_philosophers time_to_die time_to_eat\n\
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define CHARISDIGIT(c) ((c >= 48) && (c <= 57))
# define CHARISSPACE(c) (((c >= 9) && (c <= 13)) || c == 32)
# define TIMEDELAY_NS 10000

typedef unsigned long long int U_LLINT;
typedef unsigned int t_uint;

enum errors {
	philo_num_error = 1,
	pthread_create_error = 2,
};

enum msgs {
	init = -1,
	eat = 0,
	slp = 1,
	thnk = 2,
	die = 3,
	l_fork = 4,
	r_fork = 5
};


typedef struct s_philo {
	int 			id;
	pthread_t		thread_id;
	int 			last_eat_start;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	enum msgs		cur_fork;
	struct s_rules 	*rules;
}				t_philo;

typedef void (*action)(t_philo*);

typedef struct s_rules {
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int 			someone_dead;
	size_t			num_eats;
	size_t			limit_eats;
	pthread_mutex_t *dashboard;
	U_LLINT 		start_time;
	pthread_t		time_ctrl;
	action			actions[5];
}				t_rules;

typedef struct s_dinner {
	t_philo 		*philos;
	int 			philo_num;
	pthread_mutex_t *forks;
	t_rules			rules;
}				t_dinner;


int		get_philos_num(char *s);
void	get_rules(t_rules *rules, char *argv[]);
void	get_philos(t_philo **philos, int philo_num, t_dinner *dinner);
void	get_forks(pthread_mutex_t **forks, int argc);

void 	*ft_process(void *args);
void	dinner_start(t_dinner *dinner);
void	stop_dinner(t_dinner *dinner, int started_threads);
void 	*timer(void *args);

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void trying_forks(t_philo *philo);
int		is_living(t_philo *philo);

int get_cur_time(t_rules *rules, int start);
void	display_message(int timestamp, t_philo *philo, int msg);

int		ft_atoi(char *s);

#endif

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
# define PHILO_NUM_ERROR "Philosophers wrong number\n"
# define WRITE_ERROR(x) write(STDERR_FILENO, x, ft_strlen(x));
# define CHARISDIGIT(c) ((c >= 48) && (c <= 57))
# define CHARISSPACE(c) (((c >= 9) && (c <= 13)) || c == 32)
# define WAITER_PERIOD 10 * 1000
# define WAITER_LAG 10 * 1000
# define EVEN_LAG (philo->id % 2) * 1000
# define ACTIONS_NUM 5

typedef unsigned long long int U_LLINT;
typedef unsigned int t_uint;

enum e_errors {
	philo_num_error = 1,
	pthread_create_error,
};

enum e_actions {
	frk1,
	frk2,
	eat,
	slp,
	thnk,
	die,
	lim
};

enum e_forks {
	l_fork,
	r_fork
};

typedef void (*action)(void*);

typedef struct s_rules {
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int 			stop;
	int 			limit_eats;
	pthread_mutex_t *dashboard;
	U_LLINT 		start_time;
	pthread_t		time_ctrl;
	action			actions[ACTIONS_NUM];
}				t_rules;

typedef struct s_philo {
	int 			id;
	pthread_t		thread_id;
	int 			last_eat_start;
	int 			eat_num;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	enum e_forks	cur_fork;
	struct s_rules 	*rules;
}				t_philo;

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
void 	stop_dinner(t_dinner *dinner);
void 	*waiter(void *args);

void	eating(void *args);
void	sleeping(void *args);
void	thinking(void *args);
void	trying_forks(void *args);

int 	get_cur_time(t_rules *rules, int start);
void	display_message(int timestamp, t_philo *philo, int msg);
int		ft_atoi(char *s);
int 	ft_strlen(char *s);

#endif

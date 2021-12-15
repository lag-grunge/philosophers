#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# define ARG_ERROR "Usage: ./philo number_of_philosophers time_to_die time_to_eat\n\
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define PHILO_NUM_ERROR "Philosophers wrong number\n"
# define WRITE_ERROR(x) write(STDERR_FILENO, x, ft_strlen(x));
# define CHARISDIGIT(c) ((c >= 48) && (c <= 57))
# define CHARISSPACE(c) (((c >= 9) && (c <= 13)) || c == 32)
# define WAITER_PERIOD 1000
# define MIN_TIME 60
# define SIGNAL_DIE 2000
# define SIGNAL_LIM 2000
# define WAITER_LIM_LAG 0
# define WAITER_DIE_LAG ((dinner->rules.time_to_die) * 1000 - (WAITER_PERIOD / 2))
# define EVEN_LAG (philo->id % 2 == 0) * 1000
# define ACTIONS_NUM 5

typedef unsigned long long int U_LLINT;
typedef unsigned int t_uint;

enum e_errors {
	philo_num_error = 1,
	fork_create_error,
};

enum e_actions {
	frk1,
	frk2,
	eat,
	slp,
	thnk,
	die,
	lim,
	tmst
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
	int 			limit_eats;
	sem_t 			*dashboard;
	sem_t			*stop_die;
	sem_t			*stop_lim;
	U_LLINT 		start_time;
	action			actions[ACTIONS_NUM];
}				t_rules;

typedef struct s_philo {
	int 			id;
	pid_t			pid;
	int 			last_eat_start;
	sem_t 			*forks;
	int 			eat_num;
	struct s_rules 	*rules;
}				t_philo;

typedef struct s_dinner {
	t_philo 		*philos;
	int 			philo_num;
	sem_t 			*forks;
	t_rules			rules;
}				t_dinner;


int		get_philos_num(char *s);
void	get_rules(t_rules *rules, char *argv[]);
void	get_philos(t_philo **philos, int philo_num, t_dinner *dinner);
void	get_forks(sem_t **forks, int argc);

void 	*ft_process(void *args);
void	dinner_start(t_dinner *dinner);
void 	stop_dinner(t_dinner *dinner);
void 	*waiter(void *args);

void	eating(void *args);
void	sleeping(void *args);
void	thinking(void *args);
void	trying_forks(void *args);
int		stop_die(void *args);

void *waiter_die(void *args);
void *waiter_lim(void *args);

int 	get_cur_time(t_rules *rules, int start);
void	display_message(int timestamp, t_philo *philo, int msg);
int		ft_atoi(char *s);
int 	ft_strlen(char *s);
void	u_sleep(int mseconds);

int kill_em(t_dinner *dinner);

#endif

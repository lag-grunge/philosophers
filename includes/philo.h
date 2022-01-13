/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 23:02:14 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 01:10:44 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# define ARG_ERROR "Usage: ./philo number_of_philosophers time_to_die time_to_eat\n\
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define PHILO_NUM_ERROR "Philosophers wrong number\n"
# define TIME_PARAM_ERROR "Wrong time parameter\n"
# define WAITER_PERIOD 100
# define WAITER_LAG 60000
# define EVEN_LAG 2000
# define MIN_TIME 60

enum e_errors {
	philo_num_error = 1,
	time_param_error,
	pthread_create_error,
	malloc_err
};

enum e_actions {
	thnk,
	frk1,
	eat,
	slp,
	die,
	lim
};

enum e_forks {
	l_fork,
	r_fork
};

typedef unsigned long long int		t_ullint;
typedef unsigned int				t_uint;

typedef struct s_rules {
	pthread_mutex_t		*dashboard;
	pthread_mutex_t		*state_mut;
	pthread_mutex_t		*eat_mut;
	struct timeval		start_time;
	struct s_philo		*philos;
	pthread_t			time_ctrl;
	int					stop;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					limit_eats;
	int					philo_num;
	int					started_philos;
	int					*states;
}		t_rules;
typedef struct s_philo {
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	struct s_rules		*rules;
	pthread_t			thread_id;
	int					id;
	int					last_eat_start;
	int					eat_num;
	int					last;
}		t_philo;
typedef struct s_dinner {
	pthread_mutex_t		*forks;
	t_philo				*philos;
	t_rules				rules;
	int					philo_num;
}		t_dinner;

int		get_philos_num(char *s);
void	get_rules(t_rules *rules, int philo_num, char *argv[]);
void	get_philos(t_philo **philos, int philo_num, t_dinner *dinner);
void	init_mutex_arr(pthread_mutex_t **mut_arr, int philo_num, int lock);

void	*ft_process(void *args);
void	dinner_start(t_dinner *dinner);
void	stop_dinner(t_dinner *dinner);
void	*waiter_die(void *args);
void	*waiter_lim(void *args);

int		eating(void *args);
int		sleeping(void *args);
int		thinking(void *args);
int		trying_forks(void *args);

int		get_cur_time(t_rules *rules);
int		ft_atoi(char *s);
int		ft_strlen(char *s);
void	u_sleep(int mseconds);
int		get_time_param(char *s);

int		left_id(t_philo *philo, int i);
int		right_id(t_philo *philo, int i);
t_philo	*right_philo(t_philo *philo, int i);
t_philo	*left_philo(t_philo *philo, int i);
void	test(t_philo *philo);

#endif

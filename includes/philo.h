/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 23:02:14 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/02 11:46:45 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define WAITER_PERIOD 100
# define WAITER_LAG 60000
# define EVEN_LAG 10000
# define THIRD_GROUP_LAG 10000

enum e_errors {
	philo_num_error = 1,
	pthread_create_error,
	malloc_err
};

enum e_actions {
	frk1,
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

typedef unsigned long long int		t_ullint;
typedef unsigned int				t_uint;

typedef struct s_rules {
	pthread_mutex_t		*dashboard;
	pthread_t			time_ctrl;
	struct timeval			start_time;
	int					stop;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					limit_eats;
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
	int					thinker;
}		t_philo;
typedef struct s_dinner {
	pthread_mutex_t		*forks;
	t_philo				*philos;
	t_rules				rules;
	int					philo_num;
}		t_dinner;

int		get_philos_num(char *s);
void	get_rules(t_rules *rules, char *argv[]);
void	get_philos(t_philo **philos, int philo_num, t_dinner *dinner);
void	get_forks(pthread_mutex_t **forks, int argc);

void	*ft_process(void *args);
void	dinner_start(t_dinner *dinner);
void	stop_dinner(t_dinner *dinner);
void	*waiter_die(void *args);
void	*waiter_lim(void *args);

void	eating(void *args);
void	sleeping(void *args);
void	thinking(void *args);
void	trying_forks(void *args);

int		get_cur_time(t_rules *rules);
void	display_message(int timestamp, t_philo *philo, int msg);
int		ft_atoi(char *s);
int		ft_strlen(char *s);
void	u_sleep(int mseconds);

#endif

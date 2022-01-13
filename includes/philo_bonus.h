/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 00:24:00 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 08:02:57 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdint.h>
# define ARG_ERROR "Usage: ./philo number_of_philosophers time_to_die time_to_eat\n\
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define PHILO_NUM_ERROR "Philosophers wrong number\n"
# define TIME_PARAM_ERROR "Wrong time parameter\n"
# define WAITER_PERIOD 100
# define THIRD_GROUP_LAG 3000
# define EVEN_LAG 2000
# define MIN_TIME 60

enum e_errors {
	philo_num_error = 1,
	time_param_error,
	malloc_error,
	fork_create_error,
	pthread_create_error
};

enum e_actions {
	thnk,
	frk1,
	eat,
	slp,
	die,
	lim
};

typedef struct s_rules {
	struct timeval	start_time;
	sem_t			*dashboard;
	sem_t			*stop_die;
	sem_t			*lim_stop;
	sem_t			*next;
	pid_t			eat_ctrl;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				limit_eats;
}			t_rules;

typedef struct s_philo {
	struct s_rules	*rules;
	sem_t			*forks;
	sem_t			*sem_err;
	pid_t			pid;
	char			*sem_err_name;
	int				id;
	int				last_eat_start;
	int				eat_num;
	int				last;
	int				stop;
	int				philo_num;
}			t_philo;

typedef struct s_dinner {
	t_rules		rules;
	t_philo		*philos;
	sem_t		*forks;
	int			philo_num;
}			t_dinner;

void	get_rules(t_rules *rules, int philo_num, char *argv[]);
void	get_philos(t_philo **philos, int philo_num, t_dinner *dinner);
void	get_forks(sem_t **forks, int argc);
sem_t	*my_sem_open(char *filename, int value);
void	close_sems(t_dinner *dinner);

void	*ft_process(void *args);
int		dinner_start(t_dinner *dinner);
int		stop_dinner(t_dinner *dinner, int start);
void	*waiter_lim(void *args);

void	start_thread(pthread_t *th, void *(*func)(void *), t_philo *philo);
void	death_philo_operations(t_philo *philo, int timestamp);

int		eating(void *args);
int		sleeping(void *args);
int		thinking(void *args);
int		trying_forks(void *args);

int		ft_atoi(char *s);

int		get_cur_time(t_rules *rules);
int		get_philos_num(char *s);
int		ft_strlen(char *s);
void	u_sleep(int mseconds);
int		get_time_param(char *s);

#endif

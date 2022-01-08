/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 00:24:00 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/02 11:49:46 by sdalton          ###   ########.fr       */
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
# define WAITER_PERIOD 100
# define THIRD_GROUP_LAG 2000

enum e_errors {
	philo_num_error = 1,
	fork_create_error,
};

enum e_actions {
	frk1,
	eat,
	slp,
	thnk,
	die,
	lim,
	tmst,
	capt,
	left
};

typedef struct s_rules {
	struct timeval	start_time;
	sem_t		*dashboard;
	sem_t		*stop_die;
	sem_t		*lim_stop;
	sem_t		*next;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			limit_eats;
}			t_rules;

typedef struct s_philo {
	struct s_rules	*rules;
	sem_t			*forks;
	pid_t			pid;
	int				id;
	int				last_eat_start;
	int				eat_num;
	int				thinker;
}			t_philo;

typedef struct s_dinner {
	t_rules		rules;
	t_philo		*philos;
	sem_t		*forks;
	int			philo_num;
}			t_dinner;

int		get_philos_num(char *s);
void	get_rules(t_rules *rules, int philo_num, char *argv[]);
void	get_philos(t_philo **philos, int philo_num, t_dinner *dinner);
void	get_forks(sem_t **forks, int argc);

void	*ft_process(void *args);
void	dinner_start(t_dinner *dinner);
void	stop_dinner(t_dinner *dinner);
void	*waiter(void *args);

void	eating(void *args);
void	sleeping(void *args);
void	thinking(void *args);
void	trying_forks(void *args);

void	*waiter_die(void *args);
void	*waiter_lim(void *args);

int		get_cur_time(t_rules *rules);
void	display_message(int timestamp, t_philo *philo, int msg);
int		ft_atoi(char *s);
int		ft_strlen(char *s);
void	u_sleep(int mseconds);

int		kill_em(t_dinner *dinner);

#endif

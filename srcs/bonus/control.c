/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:26:24 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 10:12:46 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static int	fork_start(pid_t *pid, void *(*func)(void *), void *args)
{
	*pid = fork();
	if (*pid < 0)
		return (fork_create_error);
	else if (*pid == 0)
	{
		func(args);
		exit (0);
	}
	return (0);
}

int	dinner_start(t_dinner *dinner)
{
	int			i;
	int			ret;

	gettimeofday(&dinner->rules.start_time, NULL);
	i = 0;
	ret = 0;
	if (dinner->rules.limit_eats != -1)
		ret = fork_start(&dinner->rules.eat_ctrl, waiter_lim, dinner);
	if (ret)
		return (ret);
	while (i < dinner->philo_num)
	{
		ret = fork_start(&dinner->philos[i].pid, \
				ft_process, dinner->philos + i);
		if (ret)
		{
			dinner->philo_num = i;
			return (ret);
		}
		i++;
	}
	return (0);
}

static int	wait_child(t_dinner *dinner)
{
	int	i;
	int	j;
	int	ret;

	i = dinner->philo_num;
	i += (dinner->rules.eat_ctrl > 0);
	ret = 0;
	while (i)
	{
		j = i;
		while (j)
		{
			if (waitpid(-1, &ret, WNOHANG))
				i--;
			if (WEXITSTATUS(ret) == pthread_create_error)
				ret = pthread_create_error;
			j--;
		}
		usleep(WAITER_PERIOD);
	}
	return (ret);
}

int	stop_dinner(t_dinner *dinner, int start)
{
	int	ret;

	ret = 0;
	if (start == fork_create_error)
		kill(-1, SIGKILL);
	ret = wait_child(dinner);
	close_sems(dinner);
	free(dinner->philos);
	free(dinner);
	if (start)
		return (start);
	return (ret);
}

void	*waiter_lim(void *args)
{
	t_dinner	*dinner;
	int			i;

	dinner = args;
	i = 0;
	while (i < dinner->philo_num)
	{
		sem_wait(dinner->rules.lim_stop);
		i++;
	}
	sem_wait(dinner->rules.dashboard);
	printf("%d philosophers has eaten at least %d\n", \
		get_cur_time(&dinner->rules), dinner->rules.limit_eats);
	i = 0;
	while (i < dinner->philo_num)
	{
		sem_post(dinner->rules.stop_die);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:37:20 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/11 01:41:19 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	get_philos_num(char *s)
{
	int	num;

	num = ft_atoi(s);
	if (num >= 1 && num <= 200)
		return (num);
	write(STDERR_FILENO, PHILO_NUM_ERROR, \
			ft_strlen(PHILO_NUM_ERROR));
	exit (philo_num_error);
}

int	get_cur_time(t_rules *rules)
{
	struct timeval	tv;
	int				sec_part;
	int				usec_part;

	gettimeofday(&tv, NULL);
	sec_part = (int)(tv.tv_sec - rules->start_time.tv_sec);
	usec_part = (int)(tv.tv_usec - rules->start_time.tv_usec);
	if (usec_part < 0)
	{
		sec_part -= 1;
		usec_part += 1000000;
	}
	return (sec_part * 1000 + usec_part / 1000);
}

void	u_sleep(int mseconds)
{
	unsigned long long int	cur;
	unsigned long long int	timestamp;
	struct timeval			tv;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_usec + tv.tv_sec * 1000000;
	cur = timestamp;
	while ((int)(cur - timestamp) < mseconds)
	{
		usleep(40);
		gettimeofday(&tv, NULL);
		cur = tv.tv_usec + tv.tv_sec * 1000000;
	}
}

int	kill_em(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->philo_num)
	{
		kill(dinner->philos[i].pid, SIGTERM);
		i++;
	}
	return (0);
}

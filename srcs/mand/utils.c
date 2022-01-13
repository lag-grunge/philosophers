/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 02:33:03 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 10:16:57 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	get_time_param(char *s)
{
	int	t;

	t = ft_atoi(s);
	if (t >= MIN_TIME)
		return (t);
	write(STDERR_FILENO, TIME_PARAM_ERROR, \
			ft_strlen(TIME_PARAM_ERROR));
	exit (time_param_error);
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

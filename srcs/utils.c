#include "philo.h"

int ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int get_philos_num(char *s)
{
	int num;

	num = ft_atoi(s);
	if (num >= 1 && num <= 200)
		return (num);
	WRITE_ERROR(PHILO_NUM_ERROR)
	exit (philo_num_error);
}

int	ft_atoi(char *s)
{
	long long int	n;
	int			sign;
	t_uint	digits;

	n = 0;
	sign = 1;
	digits = 0;
	while (CHARISSPACE(*s))
		s++;
	if (*s != '-' && *s != '+' && !CHARISDIGIT(*s))
		return (0);
	else if (*s == '+' || *s == '-')
		sign = -2 * (*s++ == '-') + 1;
	while (*s == '0')
		s++;
	while (CHARISDIGIT(*s))
	{
		if (10 * n + *s - 48 < n)
			return ((sign == -1) * 0 + (sign == 1) * -1);
		n = 10 * n + *s - 48;
		s++;
	}
	n = n * sign;
	return (n);
}

int get_cur_time(t_rules *rules, int start)
{
	struct timeval 	tv;

	gettimeofday(&tv, NULL);
	if (!start)
		return ((int)(tv.tv_sec * 1000 + tv.tv_usec / 1000 - rules->start_time));
	rules->start_time = tv.tv_usec / 1000 +  tv.tv_sec * 1000;
	return (0);
}

void u_sleep(int mseconds)
{
	U_LLINT 		timestamp;
	U_LLINT 		cur;
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	timestamp = tv.tv_usec + tv.tv_sec * 1000000;
	cur = timestamp;
	while ((int)(cur - timestamp) < mseconds)
	{
		usleep(50);
		gettimeofday(&tv, NULL);
		cur = tv.tv_usec + tv.tv_sec * 1000000; 
	}
}

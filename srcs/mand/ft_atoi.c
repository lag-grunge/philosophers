#include "philo.h"

static int	check_overflow(int n1, int n2, int sign)
{
	if (sign == 1)
	{
		if (n1 > INT_MAX - n2)
			return (-1);
		else
			return (n1 + n2);
	}
	else if (sign == -1)
	{
		if (-n1 < INT_MIN + n2)
			return (-1);
		else
			return (-n1 - n2);
	}
	else
		return (0);
}

static int	get_digits(int n)
{
	t_uint	dig;

	dig = 0;
	if (!n)
		return (0);
	while (n)
	{
		n /= 10;
		dig++;
	}	
	return (dig);
}

static int	near_overflow(int digits)
{
	static int	INT_MAX_dig;

	if (!INT_MAX_dig)
		INT_MAX_dig = get_digits(INT_MAX);
	return (digits == INT_MAX_dig - 1);
}

int	ft_atoi(char *s)
{
	int		n;
	int		sign;
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
	while (CHARISDIGIT(*s) && !near_overflow(digits++))
		n = 10 * n + (*s++) - 48;
	if (CHARISDIGIT(*s) && !(CHARISDIGIT(s[1])))
		return (check_overflow(9 * n + (*s++) - 48, n, sign));
	else if (CHARISDIGIT(*s))
		return (-(sign == 1));
	else
		return (sign * n);
}

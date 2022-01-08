#include "philo.h"

static int charisdigit(char c) 
{
	return ((c >= 48) && (c <= 57));
}

static int charisspace(char c) 
{
	return (((c >= 9) && (c <= 13)) || c == 32);
}

int	ft_atoi(char *s)
{
	long long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while (charisspace(*s))
		s++;
	if (*s != '-' && *s != '+' && !charisdigit(*s))
		return (0);
	else if (*s == '+' || *s == '-')
		sign = -2 * (*s++ == '-') + 1;
	while (*s == '0')
		s++;
	while (charisdigit(*s))
	{
		if (10 * n + *s - 48 < n)
			return ((sign == -1) * 0 + (sign == 1) * -1);
		n = 10 * n + *s - 48;
		s++;
	}
	n = n * sign;
	return (n);
}


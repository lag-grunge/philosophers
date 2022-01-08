# include "philo.h"

int main(int argc, char *argv[])
{
	t_dinner	*dinner;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, ARG_ERROR, \
			ft_strlen(ARG_ERROR));
		return (1);
	}
	dinner = malloc(sizeof(t_dinner));
	dinner->philo_num = get_philos_num(argv[1]);
	get_rules(&dinner->rules, argv);
	get_forks(&dinner->forks, dinner->philo_num);
	get_philos(&dinner->philos, dinner->philo_num, dinner);
	dinner_start(dinner);
	stop_dinner(dinner);
	return (0);
}

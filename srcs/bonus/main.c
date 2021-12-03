#include "philo_bonus.h"

int main(int argc, char *argv[])
{
	t_dinner	dinner;

	if (argc < 5 || argc > 6)
	{
		WRITE_ERROR(ARG_ERROR)
		return (1);
	}
	dinner.philo_num = get_philos_num(argv[1]);
	get_rules(&dinner.rules, argv);
	get_forks(&dinner.forks, dinner.philo_num);
	get_philos(&dinner.philos, dinner.philo_num, &dinner);
	dinner_start(&dinner);
	stop_dinner(&dinner);
	return (0);
}

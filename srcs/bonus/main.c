#include "philo_bonus.h"

int main(int argc, char *argv[])
{
	t_dinner	dinner;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, ARG_ERROR, 121);
		return (1);
	}
	dinner.philo_num = get_philos_num(argv[1]);
	//	записать правила
	get_rules(&dinner.rules, argv);
	//  создать стол
	//  	вилки - массив мютексов
	get_forks(&dinner.forks, dinner.philo_num);
	//  	философы - инициализация массива структур, описывающих
	//  	данные для философа, время и его состояние
	//		создание тредов философов
	get_philos(&dinner.philos, dinner.philo_num, &dinner);
	dinner_start(&dinner);
	stop_dinner(&dinner, dinner.philo_num);
	return (0);
}

#include "philo.h"

int main(int argc, char *argv[])
{
	t_dinner	dinner;

	dinner.philo_num = get_philos_num(argv[1]);
	//	записать правила
	get_rules(dinner.rules, argv);
	//  создать стол
	//  	вилки - массив мютексов
	get_forks(&dinner.forks, dinner.philo_num);
	//  	философы - инициализация массива структур, описывающих
	//  	данные для философа, время и его состояние
	//		создание тредов философов
	get_philos(&dinner.philos, dinner.philo_num, dinner.rules);
	dinner_start(&dinner);
	stop_dinner(&dinner);
	return (0);
}

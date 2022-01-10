/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 02:19:50 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/11 02:21:12 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	main(int argc, char *argv[])
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
	get_rules(&dinner->rules, dinner->philo_num, argv);
	init_mutex_arr(&dinner->forks, dinner->philo_num, 0);
	get_philos(&dinner->philos, dinner->philo_num, dinner);
	dinner->rules.philos = dinner->philos;
	dinner_start(dinner);
	stop_dinner(dinner);
	return (0);
}

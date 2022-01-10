/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:34:02 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/11 02:13:57 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_dinner	*dinner;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, ARG_ERROR, \
			ft_strlen(ARG_ERROR));
		return (1);
	}
	dinner = (t_dinner *) malloc(sizeof(t_dinner));
	dinner->philo_num = get_philos_num(argv[1]);
	get_rules(&dinner->rules, dinner->philo_num, argv);
	get_forks(&dinner->forks, dinner->philo_num);
	get_philos(&dinner->philos, dinner->philo_num, dinner);
	dinner_start(dinner);
	stop_dinner(dinner);
	return (0);
}

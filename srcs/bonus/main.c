/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:34:02 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/13 03:18:16 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_dinner	*dinner;
	int			start;

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
	start = dinner_start(dinner);
	return (stop_dinner(dinner, start));
}

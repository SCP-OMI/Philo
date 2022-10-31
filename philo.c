/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharouh <mcharouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:59:43 by mcharouh          #+#    #+#             */
/*   Updated: 2022/09/29 18:32:01 by mcharouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int ac, char **av)
{

	t_philo *philo;
	t_ph_utils *utils;


	if (ac == 5 || ac == 6)
	{
		utils = malloc(sizeof(t_ph_utils));
		philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
		param_init(philo, utils, ac, av);
		error_checks(ac, av, utils);
		thread_create(philo);
		while(1)
		{
			//philo->loop = 0;
			if (monitoring(philo, utils))
				return (0);
		}
	}
	return(printf("Invalid number of args"));
}






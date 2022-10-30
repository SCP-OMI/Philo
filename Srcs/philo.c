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
	t_ph_utils *ph_utils;


	if (ac == 5 || ac == 6)
	{
		philo = malloc(sizeof(t_philo));
		error_checks(ac, av, &ph_utils);
		ph_utils = malloc(sizeof(t_ph_utils));
		philo = malloc(sizeof(t_philo) * ph_utils->n_philo);
		param_init(&philo, &ph_utils, ac, av);
		thread_create(philo);
		while(1)
		{
			if (routine(philo))
				return (0);
		}
	}
	return(printf("Invalid args"));
}






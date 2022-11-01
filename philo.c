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
		if(param_init(&philo, utils, ac, av) == 255)
			return(printf("Invalid arg type/range\n"));
		thread_create(philo);
		while(1)
		{
			if (monitoring(philo, utils) == EXIT)
				return (0);
			usleep(50);
		}
	}
	return(printf("Invalid number of args\n"));
}






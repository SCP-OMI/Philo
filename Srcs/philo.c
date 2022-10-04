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

#include"philosopher.h"

int main (int ac, char **av)
{
	(void) ac;
	t_philo inits;
	//t_p_utils utils;
	error_checks(ac, av);
	param_init(&inits, av);
	thread_create(&inits);
	return(0);
}


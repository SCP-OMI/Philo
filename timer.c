/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharouh <mcharouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:15:34 by mcharouh          #+#    #+#             */
/*   Updated: 2022/11/02 00:32:32 by mcharouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"

long long	get_time(long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start);
}

void	sleeper(long usec)
{
	long	time;

	time = get_time(0);
	usleep(usec * 800);
	while (get_time(time) < usec)
		usleep(100);
}

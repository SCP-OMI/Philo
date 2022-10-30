/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharouh <mcharouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:03:24 by mcharouh          #+#    #+#             */
/*   Updated: 2022/10/30 13:03:24 by mcharouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"


int exits()
{
	write(2, "Error : not enough args\n", 6);
	return(1);
}


void error_checks(int ac, char **av, t_ph_utils *utils)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) == 0)
			exits();
		if (av[i][0] == '\0')
			exits();
		if (av[i][0] == '-')
			exits();
		i++;
	}
}

int thread_create(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->utils->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return(1);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < philo->utils->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return(1);
		i += 2;
	}
	return(0);
}


void param_init(t_philo *philo,	t_ph_utils *utils, int ac, char **av)
{
	int i;
	
	init_parse(ac, av, utils, philo);
	i = 0;
	while (i < utils->n_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].loop = 0;
		philo[i].left_fork = i;
		philo[i].right_fork = i + 1;
		philo[i].last_eaten = 0;
		philo[i].utils = utils;
		if (i == utils->n_philo - 1)
			philo[i].right_fork = 0;
		pthread_mutex_init(&utils->mutex[i], NULL);
		i++;
	}

}

void init_parse(int ac, char **av, t_ph_utils *utils, t_philo *philo)
{
	utils->n_philo = atoi(av[1]);
	utils->time_to_die = atoi(av[2]);
	utils->time_to_eat = atoi(av[3]);
	utils->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		philo->loop = atoi(av[5]);
	else
		philo->loop = -1;
	philo->start = get_time(0);
	pthread_mutex_init(&utils->mutex_msg, NULL);
	utils->mutex = malloc(sizeof(pthread_mutex_t) * utils->n_philo);	
}


long get_time(long start)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start);
}

void sleeper(long usec)
{
	long time;

	time = get_time(0);
	while(get_time(time) * 1000 < usec)
		usleep(100);
}

int monitoring(t_philo *philo)
{
	int i;
	long time;

	i = 0;
	while (i < philo->utils->n_philo)
	{
		pthread_mutex_lock(&philo->utils->time);
		time = get_time(philo[i].start + philo[i].last_eaten);

		if (philo[i].n_eaten >= philo[i].meals && philo)
			return (1);
		if (time >= philo[i].utils->time_to_die)
		{
			prompt_death(&philo[i]);
			return(1);
		}
		i++;
	}
	return(0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
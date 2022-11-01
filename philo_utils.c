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


int thread_create(t_philo *philo)
{
	int i;
	long time;

	time = get_time(0);
	i = 0;
	while (i < philo->utils->n_philo)
	{
		philo[i].start = time;
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return(1);
		i += 2;
	}
	usleep(25 * philo->utils->n_philo);
	i = 1;
	while (i < philo->utils->n_philo)
	{
		philo[i].start = time;
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return(1);
		i += 2;
	}
	return(0);
}


int param_init(t_philo **philo, t_ph_utils *utils, int ac, char **av)
{
	int i;
	int err;

	err = 0;
	init_parse(ac, av, utils, &err);
	if (err == 1)
	{
		free(utils);
		return(255);
	}
	i = 0;
	*philo = malloc(sizeof(t_philo) * utils->n_philo);
	while (i < utils->n_philo)
	{
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].n_eaten = 0;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = i + 1;
		(*philo)[i].last_eaten = 0;
		(*philo)[i].utils = utils;
		if (i == utils->n_philo - 1)
			(*philo)[i].right_fork = 0;
		pthread_mutex_init(&utils->fork[i], NULL);
		i++;
	}
	return(0);
}

void init_parse(int ac, char **av, t_ph_utils *utils, int *err)
{		
	utils->n_philo = ft_atoi(av[1], err);
	utils->time_to_die = ft_atoi(av[2], err);
	utils->time_to_eat = ft_atoi(av[3], err);
	utils->time_to_sleep = ft_atoi(av[4],err);
	utils->loop = 0;
	if (ac == 6)
		utils->meals = ft_atoi(av[5], err);
	else
		utils->meals = -1;
	if (*err == 1)
		return;
	pthread_mutex_init(&utils->mutex_msg, NULL);
	pthread_mutex_init(&utils->time, NULL);
	utils->fork = malloc(sizeof(pthread_mutex_t) * utils->n_philo);	
}


long long	get_time(long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 ) + (time.tv_usec / 1000) - start);
}

void sleeper(long usec)
{
	long	time;

	time = get_time(0);
	usleep(usec * 800);
	while (get_time(time) < usec)
		usleep(100);
}

int monitoring(t_philo *philo, t_ph_utils *utils)
{
	int		i;
	long	time;

	i = 0;
	while (i < philo->utils->n_philo)
	{
		pthread_mutex_lock(&philo->utils->time);
		time = get_time(philo[i].start + philo[i].last_eaten);
		pthread_mutex_unlock(&philo->utils->time);
		if (time >= philo[i].utils->time_to_die)
			return(prompt_death(&philo[i]));
		if (utils->loop == utils->n_philo && utils->meals != -1)
			return (EXIT);
		i++;
	}
	return(1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
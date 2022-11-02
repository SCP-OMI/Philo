/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharouh <mcharouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:21:15 by mcharouh          #+#    #+#             */
/*   Updated: 2022/11/02 00:21:15 by mcharouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"

void	mini_print(t_philo *philo, char *str, long time)
{
	pthread_mutex_lock(&philo->utils->mutex_msg);
	printf("%04ld ms : Philo %d %s", time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->utils->mutex_msg);
}

void	_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->fork[philo->left_fork]);
	mini_print(philo, "has taken a fork\n", get_time(philo->start));
	pthread_mutex_lock(&philo->utils->fork[philo->right_fork]);
	mini_print(philo, "has taken a fork\n", get_time(philo->start));
	pthread_mutex_lock(&philo->utils->time);
	philo->last_eaten = get_time(philo->start);
	pthread_mutex_unlock(&philo->utils->time);
	mini_print(philo, "is eating\n", get_time(philo->start));
	sleeper(philo->utils->time_to_eat);
	pthread_mutex_lock(&philo->utils->time);
	philo->n_eaten++;
	pthread_mutex_lock(&philo->utils->looper);
	if (philo->n_eaten == philo->utils->meals && philo->utils->meals != -1)
		philo->utils->loop++;
	pthread_mutex_unlock(&philo->utils->looper);
	pthread_mutex_unlock(&philo->utils->time);
	pthread_mutex_unlock(&philo->utils->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->utils->fork[philo->right_fork]);
	mini_print(philo, "is sleeping\n", get_time(philo->start));
	sleeper(philo->utils->time_to_sleep);
	mini_print(philo, "is thinking\n", get_time(philo->start));
}

int	prompt_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->mutex_msg);
	printf("%04lld ms : philo %d died\n", \
		get_time(philo->start), philo->philo_id);
	return (EXIT);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		_routine(philo);
	}
}

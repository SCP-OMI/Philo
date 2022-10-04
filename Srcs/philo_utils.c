/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharouh <mcharouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:09:47 by mcharouh          #+#    #+#             */
/*   Updated: 2022/10/04 05:47:37 by mcharouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"


int error_checks(int ac, char **av, t_p_utils *extra)
{
	
	if (ac != 5)
		exits();
	while(ac != 1)
	{
		if (ft_atoi(av[extra->i]))
			return(write(1, "ok\n", 3));	
	}
	return (0);
	
}
/**
 * @brief hold the inital values passed by the user
 * 
 * @param inits structs holding the ints for the params
 * @param ac duh
 * @param av duh
 */
void param_init(t_philo *inits, char **av)
{
	inits->n_philo = atoi(av[1]);
	inits->time_to_die = atoi(av[2]);
	inits->time_to_eat = atoi(av[3]);
	inits->time_to_sleep = atoi(av[4]);
	inits->n_forks = inits->n_philo;
}

void thread_create(t_philo *philo)
{
	int i;
	i = 0;
	philo->t_p_utils.philo_id = philo->n_philo;
	philo->t_p_utils.fork_id = philo->n_philo;
	while (i <= philo->n_philo)
	{
		pthread_create(&id[i], NULL, (void *)routine, NULL);
		i += 2;
	}
	i = 1;
	while (i <= philo->n_philo)
	{
		pthread_create(&id[i], NULL, (void *)routine, NULL);
		i += 2;
	}
}
void routine(t_philo *philo)
{

	routine_eat(&philo);
	routine_sleep(&philo);
	routine_think(&philo);
	
}
void exits()
{
	write(1, "exit\n", 6);
	exit(0);
}

void routine_eat(t_philo *philo)
{	
	
	/*Start the time when the philo starts eating*/
	int i;
	i = 0;
	pthread_mutex_init(&philo->t_p_utils.fork_id[i],NULL);
	/*give a philo one fork on the left and one on the right*/
	pthread_mutex_lock(&philo->t_p_utils.fork_id[i])
	if (i - 1 < 0)
		pthread_mutex_lock(&philo->t_p_utils.fork_id[philo.n_philo - 1]);
	else
		pthread_mutex_lock(&philo->t_p_utils.fork_id[i - 1]);
	gettimeofday(&start, NULL);
	printf("Philo %d is eating", philo->t_p_utils.philo_id[i]);
	usleep(philo->time_to_eat);
	
	/*lock the fork once given to the philo*/
	/*Remember to put down the fork if the other is busy*/
	
}

void routine_sleep(t_philo *philo)
{}

void routine_think(t_philo *philo)
{}

void set_time()
{
	
}
/**
 * @brief Checks if the time interval between each task is in exces
 * 
 * @param philo 
 * @return true : The time of wait is greater than the one taken by the usr
 * @return false : The time of wait is lower than the one taken by the usr
 */
bool over_time(t_philo *philo)
{
	gettimeofday(&start, NULL);
	
}
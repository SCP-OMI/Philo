/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharouh <mcharouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:30:53 by mcharouh          #+#    #+#             */
/*   Updated: 2022/11/02 00:30:53 by mcharouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdatomic.h>

# define EXIT 10

typedef struct s_ph_utils
{
	int				loop;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	*fork;
	pthread_mutex_t	time;
	pthread_mutex_t	looper;

}	t_ph_utils;

typedef struct s_philo
{
	long			start;
	int				philo_id;
	int				last_eaten;
	int				n_eaten;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	t_ph_utils		*utils;
}	t_philo;

//info parsing
void		error_checks(int ac, char **av, t_ph_utils *utils);
int			ft_atoi(const char *str, int *err);

//Philo creation/inits
int			param_init(t_philo **philo,	t_ph_utils *utils, int ac, char **av);
void		init_parse(int ac, char **av, t_ph_utils *utils, int *err);
int			thread_create_pair(t_philo *philo);
int			thread_create_unpair(t_philo *philo, long time);

//Helper fucntions
long long	get_time(long start);
void		sleeper(long usec);
void		mini_print(t_philo *philo, char *str, long time);

//Routine functions
void		*routine(void *philo);
void		routine_est(t_philo *philo);

//Monitoring functions 
int			prompt_death(t_philo *philo);
int			monitoring(t_philo *philo, t_ph_utils *utils);

#endif
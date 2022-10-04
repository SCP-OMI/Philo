#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int n_philo;
	int n_forks;

	int time_to_die; //
	int time_to_eat; //
	int	time_to_sleep;
	struct s_p_utils
	{
		pthread_t philo_id;
		pthread_mutex_t fork_id;

	} t_p_utils;
}	t_philo;



//intialization functions
void param_init(t_philo *philo, char **av);
void thread_create(t_philo *philo);
//Error checking functions
int error_checks(int ac, char **av, t_p_utils *extra);
int	ft_atoi(const char *str);
void exits();
//Routine functions
void routine(t_philo *philo);
void routine_eat(t_philo *philo);
void routine_sleep(t_philo *philo);
void routine_think(t_philo *philo);
void set_time()

//Checking for the time intervals
bool over_time(t_philo *philo);

#endif

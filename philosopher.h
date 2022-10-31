#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_ph_utils
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	pthread_mutex_t mutex_msg;
	pthread_mutex_t *mutex;
	pthread_mutex_t time;

} t_ph_utils;

typedef struct s_philo
{
	int				philo_id;
	int				loop;
	int				start;
	int 			last_eaten;
	int				n_eaten;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	t_ph_utils		*utils;
}	t_philo ;

//info parsing
void		error_checks(int ac, char **av, t_ph_utils *utils);

//Philo creation/inits
void 	param_init(t_philo *philo,	t_ph_utils *utils, int ac, char **av);
void 	init_parse(int ac, char **av, t_ph_utils *utils, t_philo *philo);
int		thread_create(t_philo *philo);

//Helper fucntions
long 	get_time(long start);
int		exits();
void 	sleeper(long usec);
void	put_error(void);
int		check_edges(long long result, int sign);
int		ft_atoi(const char *str);
void 	mini_print(t_philo *philo, char *str, long time);


//Routine functions
void 	*routine(void *philo);
void	routine_eating(t_philo *philo);
void	routine_sleeping(t_philo *philo);
void	routine_thinking(t_philo *philo);


//Monitoring functions 
void	prompt_death(t_philo *philo);
int		monitoring(t_philo *philo, t_ph_utils *utils);

#endif
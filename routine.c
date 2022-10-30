#include"philosopher.h"

void mini_print(t_philo *philo, char *str, long time)
{
	pthread_mutex_lock(&philo->utils->mutex_msg);
	printf("%ld : Philo %d %s", time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->utils->mutex_msg);
}


void	routine_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->mutex[philo->left_fork]);
	mini_print(philo, "has taken a fork\n", get_time(philo->start));
	pthread_mutex_lock(&philo->utils->mutex[philo->right_fork]);
	mini_print(philo, "has taken a fork\n", get_time(philo->start));
	mini_print(philo, "has started to eat\n", get_time(philo->start));
	pthread_mutex_lock(&philo->utils->time);
	philo->loop++;
	philo->last_eaten = get_time(philo->start);
	pthread_mutex_unlock(&philo->utils->time);
	sleeper(philo->utils->time_to_eat);
	pthread_mutex_unlock(&philo->utils->mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->utils->mutex[philo->right_fork]);

}

void	routine_sleeping(t_philo *philo)
{
	mini_print(philo, "is sleeping\n", get_time(philo->start));
	sleeper(philo->utils->time_to_sleep * 100);
}

void	routine_thinking(t_philo *philo)
{
	mini_print(philo, "is thinking\n", get_time(philo->start));
}

void	prompt_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->utils->mutex_msg);
	printf("%ld : philo %d died\n", get_time(philo->start), philo->philo_id);
}

void *routine(void *philo)
{
	t_philo *philo;

	philo = (t_philo *)philo;
	while (1)
	{
		routine_eating(philo);
		routine_sleeping(philo);
		routine_thinking(philo);
	}
}
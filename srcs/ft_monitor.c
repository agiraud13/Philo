#include "philo.h"

void	ft_free_data(t_data *data)
{
	free(data->death);
	free(data->forks);
	free(data->print);
}

static void	ft_stop(t_philo *p, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		p[i].stop = 1;
		i++;
	}
}

int	ft_check_num_eat(t_philo *philo, int num_of_philo, int num_eat)
{
	int	i;

	i = 0;
	while (num_eat > 0 && philo[i].num_eat >= num_eat)
	{
		if (i == num_of_philo - 1)
		{
			ft_stop(philo, num_of_philo);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_is_life(t_philo *p, int num_of_philo, int time_to_die)
{
	int		i;

	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_lock(p->death);
		if (ft_time() - p[i].last_eat >= time_to_die)
		{
			ft_stop(p, num_of_philo);
			printf("%ld %d died\n", ft_time() - p[i].start, p[i].pos);
			pthread_mutex_unlock(p->death);
			return (1);
		}
		pthread_mutex_unlock(p->death);
		i++;
	}
	return (0);
}

void	ft_monitor(t_philo *philo, t_data *data)
{
	while (1)
	{
		if (ft_check_is_life(philo, data->num_of_philo, data->time_to_die))
			return ;
		if (ft_check_num_eat(philo, data->num_of_philo, data->num_eat))
			return ;
	}
}

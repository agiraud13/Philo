#include "philo.h"

t_data	ft_init_data(void)
{
	t_data	data;

	data.num_of_philo = 0;
	data.time_to_die = 0;
	data.time_to_eat = 0;
	data.time_to_sleep = 0;
	data.num_eat = 0;
	data.death = NULL;
	data.print = NULL;
	data.forks = NULL;
	return (data);
}

int	ft_check_data(t_data *data, int argc)
{
	int	i;

	i = 0;
	if (data->num_of_philo == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
		return (0);
	if (argc == 6)
	{
		if (data->num_eat == 0)
			return (0);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	data->death = malloc(sizeof(pthread_mutex_t));
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->forks || !data->death || !data->print)
	{
		ft_free_data(data);
		return (-1);
	}
	while (i < data->num_of_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(data->death, NULL);
	pthread_mutex_init(data->print, NULL);
	return (1);
}

t_philo	*ft_init_philos(t_data *data)
{
	t_philo			*philos;
	int				i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (!philos)
		return (NULL);
	while (i < data->num_of_philo)
	{
		philos[i].death = data->death;
		philos[i].print = data->print;
		philos[i].right = &data->forks[i];
		if (i != 0)
			philos[i].left = &data->forks[i - 1];
		philos[i].pos = i + 1;
		philos[i].stop = 0;
		philos[i].num_eat = 0;
		philos[i].time_to_sleep = data->time_to_sleep;
		philos[i].time_to_eat = data->time_to_eat;
		i++;
	}
	philos[0].left = &data->forks[data->num_of_philo - 1];
	return (philos);
}

void	ft_clear(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(data->print);
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	ft_free_data(data);
}

long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

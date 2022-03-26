#include "philo.h"

t_data	parse_argv(int argc, char **argv)
{
	t_data	data;

	data = ft_init_data();
	if (ft_isdigit(argv[1]))
		data.num_of_philo = ft_atoi(argv[1]);
	if (ft_isdigit(argv[2]))
		data.time_to_die = ft_atoi(argv[2]);
	if (ft_isdigit(argv[3]))
		data.time_to_eat = ft_atoi(argv[3]);
	if (ft_isdigit(argv[4]))
		data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (ft_isdigit(argv[5]))
			data.num_eat = ft_atoi(argv[5]);
	}
	return (data);
}

void	ft_usleep(int time)
{
	long	stop;

	stop = ft_time() + (long)time;
	while (ft_time() < stop)
		usleep(0);
}

void	*live(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1 && !p->stop && !(p->right == p->left))
	{
		pthread_mutex_lock(p->left);
		pthread_mutex_lock(p->right);
		ft_print("has taken a left fork", p);
		ft_print("has taken a right fork", p);
		pthread_mutex_lock(p->death);
		p->last_eat = ft_time();
		ft_print("is eating", p);
		pthread_mutex_unlock(p->death);
		p->num_eat++;
		ft_usleep(p->time_to_eat);
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(p->right);
		ft_print("is sleeping", p);
		ft_usleep(p->time_to_sleep);
		ft_print("is thinking", p);
	}
	return (0);
}

int	philo(t_data data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = ft_init_philos(&data);
	if (!philos)
		return (-1);
	while (i < data.num_of_philo)
	{
		philos[i].start = ft_time();
		philos[i].last_eat = philos[i].start;
		pthread_create(&philos[i].p, NULL, live, &(philos[i]));
		usleep(100);
		i++;
	}
	i = 0;
	ft_monitor(philos, &data);
	while (i < data.num_of_philo)
	{
		pthread_join(philos[i].p, NULL);
		i++;
	}
	ft_clear(&data);
	free(philos);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		check;

	if (argc == 5 || argc == 6)
	{
		data = parse_argv(argc, argv);
		check = ft_check_data(&data, argc);
		if (check)
		{
			if (philo(data) == -1)
				printf("Malloc error\n");
		}
		else if (check == -1)
			printf("Malloc error\n");
		else
		{
			printf("Not valid params\nYou should enter 4 [5] params:\n");
			printf("number_of_philosophers\ntime_to_die\ntime_to_eat\n");
			printf("time_to_sleep\n");
			printf("[optional] number_of_times_each_philosopher_must_eat\n");
		}
	}
	else
		printf("Wrong amount of params\n");
	return (0);
}

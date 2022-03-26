#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"
# include "sys/time.h"

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*death;
	pthread_mutex_t	*print;
}				t_data;

typedef struct s_philo
{
	pthread_t		p;
	int				pos;
	int				stop;
	int				time_to_sleep;
	int				time_to_eat;
	int				num_eat;
	long			start;
	long			last_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*death;
	pthread_mutex_t	*print;
}				t_philo;

int				ft_isdigit(char *str);
int				ft_atoi(const char *str);
int				ft_check_data(t_data *data, int argc);
void			ft_monitor(t_philo *philo, t_data *data);
long			ft_time(void);
void			ft_clear(t_data *data);
void			ft_free_data(t_data *data);
void			ft_print(char *str, t_philo *p);
t_data			ft_init_data(void);
t_philo			*ft_init_philos(t_data *data);

#endif

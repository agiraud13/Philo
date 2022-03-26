#include "philo.h"

void	ft_print(char *str, t_philo *p)
{
	pthread_mutex_lock(p->print);
	if (p->stop)
	{
		pthread_mutex_unlock(p->print);
		return ;
	}
	printf("%lu %d %s\n", ft_time() - p->start, p->pos, str);
	pthread_mutex_unlock(p->print);
}

#include <stdio.h>
#include "sys/time.h"

int main()
{
    struct timeval	tv;

	gettimeofday(&tv, NULL);
    printf("1 : afficher l'heure %ld\n", tv.tv_sec * 1000 + tv.tv_usec / 1000);
    printf("2 : afficher l'heure %d\n", tv.tv_usec);
    return (0);
}
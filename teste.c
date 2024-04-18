/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:25:55 by mfassbin          #+#    #+#             */
/*   Updated: 2024/04/17 18:10:52 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int n = 0;

void *routine(void *m)
{
    pthread_mutex_lock((pthread_mutex_t *)m);
    int i = 0;
    while(i < 1000000000)
    {
         i++;
         n++;
    }   
    pthread_mutex_unlock((pthread_mutex_t *)m);
    return(NULL);
}

int main(void)
{
    pthread_t p1, p2;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&p1, NULL, &routine, &mutex);
    pthread_create(&p2, NULL, &routine, &mutex);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("o valor de n eh: %i\n", n);    
}
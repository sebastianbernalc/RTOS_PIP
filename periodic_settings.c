/*************************************************/

// Prof. Luca Abeni. The Real-Time Operating Systems and Middleware course
// http://www.dit.unitn.it/~abeni/RTOS/periodic_tasks.c

/*************************************************/

/*************************************************/
//  - Code modified by Prof. Gustavo Patino  -
//    - Real-Time Systems (IEO 2547027) -
//     - University of Antioquia (UdeA) -
//      - Medellin, Colombia 2022 -
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>

#include "periodic_settings.h"

#define NSEC_PER_SEC 1000000000ULL

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void current_time()
{
	time_t sec;
	suseconds_t	msec;
	char zeros[3];	
	
	struct timeval tv;
	
	gettimeofday(&tv, 0);

	sec = tv.tv_sec;
	msec = tv.tv_usec/1000;
	
	if (msec < 10)
		strcpy(zeros, "00");
	else if (msec < 100)
		strcpy(zeros, "0");
	else 		
		strcpy(zeros, "");
		
	printf("\nEl tiempo actual en segundos es: %ld.%s%ld\n", sec, zeros, msec);	
}


void timespec_add_us(struct timespec *t, uint64_t d)
{
// El valor d que llega es en us, entonces se agrega al timespec *t en nanosegundos, multiplicado por 1000. (d*1000 nsec = d usec) 
// Por esto la funcion se llama "timespec_add_us", o sea, agrega us al timespec.

	#ifdef DEBUG_MODE
		printf("\ntimespec t, component sec =  %ld\n", t->tv_sec);
		printf("timespec t, component nsec =  %ld\n", t->tv_nsec);
	#endif

	d *= 1000;
	d += t->tv_nsec;
	while (d >= NSEC_PER_SEC) {
		d -= NSEC_PER_SEC;  // Por cada resta de NSEC_PER_SEC debe agregar un segundo al tv_sec.
		t->tv_sec += 1;
	}
	t->tv_nsec = d;
}


void wait_next_activation(struct periodic_thread *t)
{
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &t->r, NULL);
    timespec_add_us(&t->r, t->period);
}


void start_periodic_timer(struct periodic_thread* perthread)
{

	clock_gettime(CLOCK_REALTIME, &perthread->r);
	timespec_add_us(&perthread->r, perthread->offset);
}

void log_message(const char *message, const char *filename)
{
    pthread_mutex_lock(&mutex);

    FILE *fp = fopen(filename, "a");
    if (fp != NULL)
    {
        fprintf(fp, "%s\n", message);
        fclose(fp);
    }

    pthread_mutex_unlock(&mutex);
}

int timespec_cmp(struct timespec *a, struct timespec *b)
{
    if (a->tv_sec > b->tv_sec)
        return 1;
    else if (a->tv_sec < b->tv_sec)
        return -1;
    else if (a->tv_sec == b->tv_sec)
    {
        if (a->tv_nsec > b->tv_nsec)
            return 1;
        else if (a->tv_nsec == b->tv_nsec)
            return 0;
        else
            return -1;
    }
}
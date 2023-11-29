/*************************************************/
//  - Code by Prof. Gustavo Patino  -
//    - Real-Time Systems (IEO 2547027) -
//     - University of Antioquia (UdeA) -
//      - Medellin, Colombia 2022 -
/*************************************************/

#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t lock;

void *sched_bus_task(int wcet);
void *data_task(int wcet);
void *control_task(int wcet);
void *radio_task(int wcet);
void *video_task(int wcet);


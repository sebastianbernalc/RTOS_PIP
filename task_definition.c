/*************************************************/
//  - Code by Prof. Gustavo Patino  -
//    - Real-Time Systems (IEO 2547027) -
//     - University of Antioquia (UdeA) -
//      - Medellin, Colombia 2022 -
/*************************************************/


#include "task_definition.h"


void *sched_bus_task(int wcet)
{
    usleep(wcet);
}

void *data_task(int wcet)
{
    usleep(wcet);
}

void *control_task(int wcet)
{
    usleep(wcet);
	
}

void *radio_task(int wcet)
{
    usleep(wcet);
	
}

void *video_task(int wcet)
{
    usleep(wcet);
}

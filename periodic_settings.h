/*************************************************/

// Prof. Luca Abeni. The Real-Time Operating Systems and Middleware course
// http://www.dit.unitn.it/~abeni/RTOS/periodic_tasks.h

/*************************************************/


/*************************************************/
//  - Code by Prof. Gustavo Patino  -
//    - Real-Time Systems (IEO 2547027) -
//     - University of Antioquia (UdeA) -
//      - Medellin, Colombia 2022 -
/*************************************************/


struct periodic_thread {
	struct timespec r;
	int thread_id;
	int period;
	int offset;
	uint32_t wcet;
};

void current_time();
void timespec_add_us(struct timespec *t, uint64_t d);
void start_periodic_timer(struct periodic_thread* perthread);

void wait_next_activation(struct periodic_thread *t);

int timespec_cmp(struct timespec *a, struct timespec *b);
void log_message(const char *message, const char *filename);

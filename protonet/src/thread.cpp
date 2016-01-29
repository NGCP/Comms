#include <thread.h>

/* Aside from the function pointer taking void* as argument and returning void*, nothing special here */
#ifdef __unix__
void thread_create(thread_t* thread, void* (*start_routine) (void *), void* arg)
{
	pthread_create(thread, NULL,start_routine, arg);
}

void thread_set_priority(thread_t* thread, int32_t priority)
{
	pthread_setschedprio(thread, priority);
}

thread_t thread_get_self_id()
{
    return pthread_self();
}

#endif


#ifdef _WIN32
void thread_create(thread_t* thread, void *(*start_routine) (void *), void* arg)
{
	*thread= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) start_routine, arg, 0, NULL);
}

void thread_set_priority(thread_t* thread, int32_t priority)
{
	SetThreadPriority(thread, priority);
}

thread_t thread_get_self_id()
{
    return GetCurrentThread();
}

#endif

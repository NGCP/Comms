/* 

Lightweight cross platform thread wrapper for
Windows and POSIX.

*/
#ifndef _THREAD_H
#define _THREAD_H

#ifdef _WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"ws2_32.lib")
/** Define Windows typedef of threading data type*/
typedef HANDLE thread_t;
#endif


#ifndef _WIN32
#include <pthread.h>
#include <stdint.h>
/** Define Linux typedef of threading data type*/
typedef pthread_t thread_t;
#endif

extern "C"
{
/** Global C function to create thread*/
void thread_create(thread_t* thread, void *(*start_routine) (void *), void* arg);
/** Global C function to set thread priority */
void thread_set_priority(thread_t* thread, int32_t priority);
/** GLobal C function which returns thread id */
thread_t thread_get_self_id();
}
#endif

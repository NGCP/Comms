/** @file
Lightweight cross platform mutex wrapper for
Windows and POSIX.
*/
#ifndef _MUTEX_H
#define _MUTEX_H

#ifndef _WIN32
#include <pthread.h>
typedef pthread_mutex_t mutex_t;
#endif

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"ws2_32.lib")
typedef HANDLE mutex_t;
#endif

/** Global Mutex function which initalization the parameter mutex*/
void mutex_init(mutex_t* mutex);
/** GLobal Mutex function which unlock the the parameter mutex*/
void mutex_unlock(mutex_t* mutex);
/** GLobal Mutex function which locks the the parameter mutex*/
void mutex_lock(mutex_t* mutex);
/** GLobal Mutex function which close the the parameter mutex*/
void mutex_destroy(mutex_t* mutex);	


#endif
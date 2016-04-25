/**
Lightweight cross platform condition variable
wrapper for Windows and POSIX threading. Function descriptions taken from http://linux.die.net
*/

#ifndef _COND_H
#define _COND_H
#include <mutexCom.h>

#ifndef _WIN32
#include <pthread.h>
typedef pthread_cond_t cond_t;
#endif

#ifdef _WIN32

#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"ws2_32.lib")

typedef struct cond_s
{
  /**Number of waiting threads.*/  
  int waiters_count_;
  
  /** Serialize access to <waiters_count_>.*/
  CRITICAL_SECTION waiters_count_lock_;
  
  /** Semaphore used to queue up threads waiting for the condition to
   become signaled.*/
  HANDLE sema_;
 
  /** An auto-reset event used by the broadcast/signal thread to wait
  for all the waiting thread(s) to wake up and be released from the
  semaphore. */
  HANDLE waiters_done_;
 

  /** Keeps track of whether we were broadcasting or signalling.  This
   allows us to optimize the code if we're just signalling.*/  
  size_t was_broadcast_;

} cond_t;
#endif

/** Global function Initialize condition parameter*/
void cond_init(cond_t* cv);
/** Global function shall unblock at least one of the threads 
that are blocked on the specified condition variable cond (if any threads are blocked on cond).*/
void cond_signal (cond_t *cv);
/** Global function shall block on a condition variable. They shall be called 
with mutex locked by the calling thread or undefined behavior results. */
void cond_wait(cond_t *cv, mutex_t *external_mutex);
/** Global function shall unblock all threads currently blocked 
on the specified condition variable cond.*/
void cond_broadcast (cond_t *cv);

#endif	

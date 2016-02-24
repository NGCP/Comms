/* User Include */
#include <mutex.h>



#ifdef __unix__

void mutex_init(mutex_t* mutex)
{
	pthread_mutex_init(mutex, NULL);
}
void mutex_unlock(mutex_t* mutex)
{
	pthread_mutex_unlock(mutex);
}
void mutex_lock(mutex_t* mutex)
{
	pthread_mutex_lock(mutex);
}
void mutex_destroy(mutex_t* mutex)
{
	pthread_mutex_destroy(mutex);
}

#endif




#ifdef _WIN32

void mutex_init(mutex_t* mutex)
{
	*mutex = CreateMutex(NULL, FALSE, NULL);
}
void mutex_unlock(mutex_t* mutex)
{
	ReleaseMutex(*mutex);
}
void mutex_lock(mutex_t* mutex)
{
	WaitForSingleObject(*mutex, INFINITE);
}
void mutex_destroy(mutex_t* mutex)
{
	CloseHandle(*mutex);
}

#endif


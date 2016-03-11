#ifndef _QUEUE_H
#define _QUEUE_H

/* System Includes */
#include <list>

/* User Includes */
#include <cond.h>
#include <mutexCom.h>
#include <comnet_message.h>
#include <priority_queue.h>
#include <queue>

/** Namespace comnet includes abstract class datalink and the message queue class. */
namespace comnet
{

/**
 A threadsafe cross platform message queue.

 Used to transmit parsed comnet messages between
 the datalink handler and comnet event handler.
*/
class com_msg_queue
{
public:    
	com_msg_queue();
	~com_msg_queue();
	void add(com_msg_t* msg);
	void remove(com_msg_t* msg);
	int32_t size();
	

private:
	/** Mutex and condition variable used for locking and thread safety */
	mutex_t mutex;
	cond_t cond;
	/** Uses a std list, possible performance hit? */
	libtools::PriorityQueue_Interface<uint16_t, com_msg_t>* queue;
};

}
#endif
#ifndef _QUEUE_H
#define _QUEUE_H

/* System Includes */
#include <list>

/* User Includes */
#include <cond.h>
#include <mutex.h>
#include <protonet_message.h>

/** Namespace protonet includes abstract class datalink and the message queue class. */
namespace protonet
{

/**
 A threadsafe cross platform message queue.

 Used to transmit parsed protonet messages between
 the datalink handler and protonet event handler.
*/
class proto_msg_queue
{
public:    
	proto_msg_queue();
	~proto_msg_queue();
	void add(proto_msg_t* msg);
	void remove(proto_msg_t* msg);
	int32_t size();
	

private:
	/** Mutex and condition variable used for locking and thread safety */
	mutex_t mutex;
	cond_t cond;
	/** Uses a std list, possible performance hit? */
	std::list<proto_msg_t> queue;
};

}
#endif
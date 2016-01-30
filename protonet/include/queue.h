#ifndef _QUEUE_H
#define _QUEUE_H

/* System Includes */
#include <list>

/* User Includes */
#include <cond.h>
#include <mutex.h>
#include <protonet_message.h>
#include <priority_queue.h>
#include <queue>

// THIS IS A GIANT TEST MACRO DESIGNED TO IMPLEMENT AND TEST THE RBTREE VS. 
// THE STANDARD C++ LIBRARY LIST. HIGHLY RECOMMEND AGAINST THIS IN THE RELEASE
// VERSION.
//-------------------------------------------------------------------------------
#define LEGACY_DATA_STRUCT                              1
#if defined(LEGACY_DATA_STRUCT)
 #if LEGACY_DATA_STRUCT /* PRIORITY_QUEUE IS 1*/
  #define _QUEUE_                 libtools::PriorityQueue_Interface<uint16_t, proto_msg_t>*
  #define _CREATE_QUEUE_()         (queue = new libtools::LinkedPriorityQueue<uint16_t, proto_msg_t>())
  #define _DELETE_QUEUE_()         delete queue; queue = NULL;
  #define _ADD_TO_QUEUE_(msg)     queue->enqueue(msg->header.is_emergency, *msg)
  #define _REMOVE_FROM_QUEUE(msg) queue->dequeue()
  #define _QUEUE_SIZE_(queue)     queue->get_size()
  #define _QUEUE_IS_EMPTY(queue)  queue->is_empty()
 #endif 
#else/* QUEUE*/
 #define _QUEUE_                 std::list<proto_msg_t>
 #define _CREATE_QUEUE_      
 #define _DELETE
 #define _ADD_TO_QUEUE_(msg)     queue.push_back(*msg)
 #define _REMOVE_FROM_QUEUE(msg) queue.front(); queue.pop_front();
 #define _QUEUE_SIZE_(queue)     queue.size()
 #define _QUEUE_IS_EMPTY(queue)  queue.size() == 0
#endif 
#undef TEST_RBTREE
//-------------------------------------------------------------------------------


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
	_QUEUE_ queue;
};

}
#endif
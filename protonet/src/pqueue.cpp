#include <pqueue.h>
#include <mutex.h>
using namespace protonet;

	proto_msg_queue::proto_msg_queue()
	{    
		mutex_init(&mutex);
		cond_init(&cond);
        queue = new libtools::LinkedPriorityQueue<uint16_t, proto_msg_t>();
	}
	proto_msg_queue::~proto_msg_queue()
	{
    		printf("Queue is deleted!!");
		delete queue;
	}
	void proto_msg_queue::add(proto_msg_t* msg)
	{
		mutex_lock(&mutex);
		queue->enqueue(msg->header.is_emergency, *msg);
		cond_signal(&cond);
		mutex_unlock(&mutex);
	}
	void proto_msg_queue::remove(proto_msg_t* msg)
	{
		mutex_lock(&mutex);
		while(queue->is_empty())
		{
			cond_wait(&cond, &mutex);
		}
		*msg = queue->dequeue();
		//queue.pop_front();
		mutex_unlock(&mutex);
		
	}

	int32_t proto_msg_queue::size()
	{
		mutex_lock(&mutex);
		int32_t size = queue->get_size();
		mutex_unlock(&mutex);
		return size;
	}

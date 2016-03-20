#include <pqueue.h>
#include <mutexCom.h>
using namespace comnet;

	com_msg_queue::com_msg_queue()
	{    
		mutex_init(&mutex);
		cond_init(&cond);
        queue = new libtools::LinkedPriorityQueue<uint16_t, com_msg_t>();
	}
	com_msg_queue::~com_msg_queue()
	{
    		printf("Queue is deleted!!");
		delete queue;
	}
	void com_msg_queue::add(com_msg_t* msg)
	{
		mutex_lock(&mutex);
		queue->enqueue(msg->header.is_emergency, *msg);
		cond_signal(&cond);
		mutex_unlock(&mutex);
	}
	void com_msg_queue::remove(com_msg_t* msg)
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

	int32_t com_msg_queue::size()
	{
		mutex_lock(&mutex);
		int32_t size = queue->get_size();
		mutex_unlock(&mutex);
		return size;
	}

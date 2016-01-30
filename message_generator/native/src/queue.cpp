#include <queue.h>
#include <mutex.h>
using namespace protonet;

	proto_msg_queue::proto_msg_queue()
	{    
		mutex_init(&mutex);
		cond_init(&cond);
        _CREATE_QUEUE_();
	}
	proto_msg_queue::~proto_msg_queue()
	{
    	printf("Queue is deleted!!");
		_DELETE_QUEUE_();
	}
	void proto_msg_queue::add(proto_msg_t* msg)
	{
		mutex_lock(&mutex);
		_ADD_TO_QUEUE_(msg);
		cond_signal(&cond);
		mutex_unlock(&mutex);
	}
	void proto_msg_queue::remove(proto_msg_t* msg)
	{
		mutex_lock(&mutex);
		while(_QUEUE_IS_EMPTY(queue))
		{
			cond_wait(&cond, &mutex);
		}
		*msg = _REMOVE_FROM_QUEUE(msg);
		//queue.pop_front();
		mutex_unlock(&mutex);
		
	}

	int32_t proto_msg_queue::size()
	{
		mutex_lock(&mutex);
		int32_t size = _QUEUE_SIZE_(queue);
		mutex_unlock(&mutex);
		return size;
	}

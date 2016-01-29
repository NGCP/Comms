#include <queue.h>
#include <mutex.h>
using namespace protonet;

	proto_msg_queue::proto_msg_queue()
	{
		mutex_init(&mutex);
		cond_init(&cond);
	}
	proto_msg_queue::~proto_msg_queue()
	{
	}
	void proto_msg_queue::add(proto_msg_t* msg)
	{
		mutex_lock(&mutex);
		queue.push_back(*msg);
		cond_signal(&cond);
		mutex_unlock(&mutex);
	}
	void proto_msg_queue::remove(proto_msg_t* msg)
	{
		mutex_lock(&mutex);
		while(queue.size() == 0)
		{
			cond_wait(&cond, &mutex);
		}
		*msg = queue.front();
		queue.pop_front();
		mutex_unlock(&mutex);
		
	}

	int32_t proto_msg_queue::size()
	{
		mutex_lock(&mutex);
		int32_t size = (int32_t)queue.size();
		mutex_unlock(&mutex);
		return size;
	}

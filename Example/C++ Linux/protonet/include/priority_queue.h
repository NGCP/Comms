#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_
#pragma once

#ifndef __cplusplus
 #error Priority Queue not compatible with this compiler!
#endif

/** tools namespace */
namespace libtools
{
	/** Interface in which our Priority Queue must have.*/
	template<typename K, typename V>
	class PriorityQueue_Interface
	{
	public:
		/** Destructor for the Priority Queue interface*/
		virtual ~PriorityQueue_Interface(void) { }

		/** Adds the key and value pair to the priority queue*/
		virtual void enqueue(K key, V value) = 0;

		/** Removes the front (first) key value pair from the priority queue.
		This results in FIFO removal from the list.*/
		virtual V dequeue(void) = 0;

		/** peeks at the front of the priority queue.*/
		virtual const V& front(void) const = 0;
		/** Grabs the current size of the queue.*/
		virtual int32_t get_size(void) const = 0;
		/** Checks if the queue is empty (true) or not (false).*/
		virtual bool is_empty(void) const = 0;
	};

	/** Our beautiful template Linked List Priority queue!
	This data structure uses a singly linked list for 
	handling priority and enqueuing and dequeuing values added.*/
	template<typename K, typename V>
	class LinkedPriorityQueue : public PriorityQueue_Interface<K,V>
	{
	private:
		/** Struct queue*/
		struct q_node
		{
			q_node* next;

			K key;
			V value;
		};
		/** size of the queue*/
		int32_t size;
		
		/** Starting root, the front of the queue*/
		q_node* root;

	protected:

	public:
		/** Constructor for the priority queue.*/
		LinkedPriorityQueue(void) : size(0), root(NULL) { }

		/** Destructor for the priority queue!*/
		virtual ~LinkedPriorityQueue(void)
		{
			q_node* previous;
			q_node* traverse = root;

			while (traverse != NULL)
			{
				previous = traverse;
				traverse = traverse->next;

				delete previous;
				previous = NULL;
			}

			root = NULL;
		}

		/** Add the key value pair into the list.*/
		void enqueue(K key, V data)
		{
			/** allocate space on the heap*/
			q_node* new_node(new q_node);

			/** initialize new node*/
			new_node->next = NULL;
			new_node->key = key;
			new_node->value = data;

			/** check if root is null.*/
			if (root == NULL)
				root = new_node;
			else
			{
				/** check if root key is less than the new node key.*/
				if (root->key < key)
				{
					/** add the new node in front of root, then have root become new node.*/
					new_node->next = root;
					root = new_node;
					size++;
				}
				else
				{
					/** keep track of previous node. traverse to next node.*/
					q_node* previous = root;
					q_node* traverse = root->next;
					/** traverse through list and find a spot for new node.*/
					while (traverse != NULL)
					{
						if (traverse->key < key)
						{
							previous->next = new_node;
							new_node->next = traverse;
							size++; 
							break;
						}

						previous = traverse;
						traverse = traverse->next;
					}
					/** If traverse reached the end of list (to the point of NULL), 
					add the new node to back of list. Traverse being NULL is 
					guaranteed that new node hasn't been added yet, and has reached the 
					end of the list. If traverse is false, new node had already been added.*/
					if (traverse == NULL)
					{
						previous->next = new_node;
						size++;
					}
				}
			}
		}
	
		/** Dequeue the front of the list. Remove front.*/
		virtual V dequeue(void)
		{
			/** removal node, which is root.*/
			q_node* rem_node = root;
			/** have root point to the next in list.*/
			root = root->next;
			/** copy value before deleting the node, then return output.*/
			V output = rem_node->value;
			
			delete rem_node; rem_node = NULL;
			
			size--;

			return output;
		}

		/** Peeks the front of the list.*/
		virtual const V& front(void) const
		{
			return root->value;
		}

		/** Grabs the current size of the list.*/
		int32_t get_size(void) const
		{
			return size;
		}

		/** check if list is empty (true), or not (false).*/
		virtual bool is_empty(void) const
		{
			return size == 0;
		}
	};
} 

#endif /* _PRIORITYQUEUE_H_ */

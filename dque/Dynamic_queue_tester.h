/*************************************************
 * Dynamic_queue_tester
 * A class for testing dynamic queues-as-arrays.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-8 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef DYNAMIC_QUEUE_TESTER_H
#define DYNAMIC_QUEUE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Dynamic_queue.h"

#include <iostream>

template <typename Type>
class Dynamic_queue_tester:public Tester< Dynamic_queue<Type> > {
	using Tester< Dynamic_queue<Type> >::object;
	using Tester< Dynamic_queue<Type> >::command;

	public:
		Dynamic_queue_tester( Dynamic_queue<Type> *obj = 0 ):Tester< Dynamic_queue<Type> >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For dynamic queues-as-arrays, these include:
 *
 *  Constructors
 *
 *   new             constructor     create a queue with the default array size
 *   new: n          constructor     create a queue with an array size of n
 *
 *  Accessors
 *
 *   size n          size            the size equals n
 *   capacity n      capacity        the capcity equals n
 *   empty b         empty           the result is the Boolean value b
 *   head n          head            n is the first element in the queue
 *   head!           head            the underflow exception is thrown
 *
 *  Mutators
 *
 *   enqueue n       enqueue         the element can be enqueued (always succeeds)
 *   dequeue n       dequeue         the head can be dequeued
 *   dequeue!        dequeue         the underflow exception is thrown
 *
 *  Others
 *
 *   assign          operator =      assign this queue to a new queue
 *   summary                         prints the amount of memory allocated
 *                                   minus the memory deallocated
 *   details                         prints a detailed description of which
 *                                   memory was allocated with details
 *   !!                              use the previous command, e.g.  5 push_front 3
 *                                                                   6 !! 7         // same as push_front 7
 *   !n                              use the command used in line n  7 front 7
 *                                                                   8 !7 9         // same as push_front 9
 *
 ****************************************************/

template <typename Type>
void Dynamic_queue_tester<Type>::process() {
	if ( command == "new" ) {
		object = new Dynamic_queue<Type>();
		std::cout << "Okay" << std::endl;
	} else if ( command == "new:" ) {
		int n;
		std::cin >> n;
		object = new Dynamic_queue<Type>( n );
		std::cout << "Okay" << std::endl;
	} else if ( command == "size" ) {
		// check if the size equals the next integer read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if ( actual_size == expected_size ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in size(): expecting the value '" << expected_size << "' but got '" << actual_size << "'" << std::endl;
		}
	} else if ( command == "capacity" ) {
		// check if the capacity equals the next integer read

		int expected_capacity;

		std::cin >> expected_capacity;

		int actual_capacity = object->capacity();

		if ( actual_capacity == expected_capacity ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in capacity(): expecting the value '" << expected_capacity << "' but got '" << actual_capacity << "'" << std::endl;
		}
	} else if ( command == "empty" ) {
		// check if the empty status equals the next Boolean read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if ( actual_empty == expected_empty ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in empty(): expecting the value '" << expected_empty << "' but got '" << actual_empty << "'" << std::endl;
		}
	} else if ( command == "head" ) {
		// checks if the first integer in the queue equals the next integer read

		Type expected_head;

		std::cin >> expected_head;

		Type actual_head = object->head();

		if ( actual_head == expected_head ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in head(): expecting the value '" << expected_head << "' but got '" << actual_head << "'" << std::endl;
		}
	} else if ( command == "head!" ) {
		// head of an empty queue - catch an exception

		Type actual_head;

		try {
			actual_head = object->head();
			std::cout << "Failure in head(): expecting to catch an exception but got '" << actual_head << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in head(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "enqueue" ) {
		// enqueue the next integer read to the front of the queue

		Type obj;

		std::cin >> obj;

		object->enqueue( obj );
		std::cout << "Okay" << std::endl;
	} else if ( command == "dequeue" ) {
		// dequeue the first integer from the queue

		Type expected_dequeued_element;

		std::cin >> expected_dequeued_element;

		Type actual_dequeued_element = object->dequeue();

		if ( actual_dequeued_element == expected_dequeued_element ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in dequeue(): expecting the value '" << expected_dequeued_element << "' but got '" << actual_dequeued_element << "'" << std::endl;
		}
	} else if ( command == "dequeue!" ) {
		// dequeue from an empty queue - catch an exception

		Type actual_dequeued_element;

		try {
			actual_dequeued_element = object->dequeue();
			std::cout << "Failure in dequeue(): expecting to catch an exception but got '" << actual_dequeued_element << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in dequeue(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "clear" ) {
		object->clear();

		std::cout << "Okay" << std::endl;
	} else if ( command == "assign" ) {
		Dynamic_queue<Type> *new_object = new Dynamic_queue<Type>();

		*new_object = *(object);

		std::cout << "Okay" << std::endl;

		Dynamic_queue_tester<Type> tester( new_object );

		tester.run();
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif
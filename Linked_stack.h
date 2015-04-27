/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID: bkinuthi@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission: (Winter) 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

/**********************************************************
 * YOU MUST MODIFY THIS FUNCTION IF YOU DID NOT IMPLEMENT
 * Single_list.h IN PROJECT 1.  THIS REQUIRES YOU TO:
 *   1.  Change which header file is is included.
 *   2.  Change the type of the member variable 'list'.
 *   3.  Update the ostream<< operator so that it prints
 *       out the entries in your implementation.
 **********************************************************/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_sentinel_list.h"
#include "Exception.h"
#include <iostream>

template <typename Type>
class Linked_stack {
	private:
		static int const ARRAY_CAPACITY = 8;

		Double_sentinel_list<Type *> list;
		int itop;
		int stack_size;

	public:
		Linked_stack();
		Linked_stack( Linked_stack const & );
		~Linked_stack();

		bool empty() const;
		int size() const;
		int list_size() const;

		Type top() const;

		void swap( Linked_stack & );
		Linked_stack &operator=( Linked_stack );
		void push( Type const &obj );
		Type pop();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Linked_stack<T> const & );
};

template <typename Type>
Linked_stack<Type>::Linked_stack():
stack_size( 0 ) {
	// Empty constructor
}

template <typename Type>
Linked_stack<Type>::Linked_stack( Linked_stack const &stack ):
itop( stack.itop ),
stack_size( stack.stack_size ) {
	// enter your implementation here
	if (stack.empty()){
		return;
	}
	//iterate through the list copying values in the array to the copy list
	//copy only what was saved (upto itop index) in the first node and everything else 
	//in the other nodes
	else {

		for ( Double_node<Type *> *ptr = stack.list.head()->next(); ptr != stack.list.tail(); ptr = ptr->next() ) {

			if ( ptr == stack.list.head()->next() ) {

				Type *cpyArray = new Type[ARRAY_CAPACITY];

				for ( int i = 0; i <= stack.itop; ++i ) {
					cpyArray[i] = stack.list.front()[i];
				}
				list.push_back(cpyArray);

			} else {
				Type *cpyArray = new Type[ARRAY_CAPACITY];
				for ( int i = 0; i <= ARRAY_CAPACITY - 1; ++i ) {
					cpyArray[i] = ptr->retrieve()[i];
				}
			}

		}




}

}
//pop all the nodes off the list
template <typename Type>
Linked_stack<Type>::~Linked_stack() {
	while(!empty()){
		pop();
	}
}

template <typename Type>
bool Linked_stack<Type>::empty() const {
	//empty return boolean:true if stack size is 0
	return ( stack_size == 0 );
}

template <typename Type>
int Linked_stack<Type>::size() const {
	// return the size of the stack
	return stack_size;
}

// Do not change this implementation

template <typename Type>
int Linked_stack<Type>::list_size() const {
	return list.size();
}

template <typename Type>
Type Linked_stack<Type>::top() const {
	//throw exception if list is empty
	if (empty()){
		throw underflow();
	}
	//access array from the front node using itop index
	return list.front()[itop];
}

template <typename Type>
void Linked_stack<Type>::swap( Linked_stack<Type> &stack ) {
	std::swap( list, stack.list );
	std::swap( stack_size, stack.stack_size );
	std::swap( itop, stack.itop );
}

template <typename Type>
Linked_stack<Type> &Linked_stack<Type>::operator=( Linked_stack<Type> rhs ) {
	swap( rhs );

	return *this;
}

template <typename Type>
void Linked_stack<Type>::push( Type const &obj ) {
	// if list is empty or the array of the front node is full, 
	//push in a new array and set itop to 0.
	//set obj to index: itop of the array
	if(itop == ARRAY_CAPACITY - 1 || empty() ){
		list.push_front(new Type[ARRAY_CAPACITY]);
		itop = 0;
		list.front()[itop] = obj;
		++stack_size;
	}
	//if array isn't full, add obj
	else{
		itop++;
		list.front()[itop] = obj;
		++stack_size;
	}
}

template <typename Type>
Type Linked_stack<Type>::pop() {
	//if list is empty, throw exception
	if(empty() ){
		throw underflow();
	}
	//return value at itop
	//if itop is 0, delete node, shift itop to next node
	//decrease stack size by 1
	else if (itop == 0){
		Type onlyEntry = list.front()[itop];
		delete [] list.front();
		list.pop_front();
		itop = ARRAY_CAPACITY - 1;
		--stack_size;
		return onlyEntry;
	}
	//return value at itop, decrease itop and stack size by 1
	else{
		Type onlyEntry = list.front()[itop];
		itop -= 1;
		stack_size -= 1;
		return onlyEntry;
	}

		
}

// You will be required to modify this function in order to accomodate
// your implementation of a singly linked list in Project 1.

template <typename T>
std::ostream &operator<<( std::ostream &out, Linked_stack<T> const &stack ) {
	if ( stack.list.size() == 0 ) {
		out << "->0";
	} else if ( stack.list.size() == 1 ) {
		out << "->[ ";

		for ( int i = 0; i <= stack.itop; ++i ) {
			out << stack.list.front()[i] << " ";
		}

		out << "]->0";
	} else {
		out << "->";

		for ( Double_node<T *> *ptr = stack.list.head()->next(); ptr != stack.list.tail(); ptr = ptr->next() ) {
			out << "[ ";

			if ( ptr == stack.list.head()->next() ) {
				for ( int i = 0; i <= stack.itop; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			} else {
				for ( int i = 0; i <= Linked_stack<T>::ARRAY_CAPACITY - 1; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			}

			out << "]->";
		}

		out << "0";
	}

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif

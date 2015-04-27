/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  bkinuthi @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2015
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

#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "ece250.h"
#include "Exception.h"

template <typename Type>
class Dynamic_queue {
    private:
        int initial_capacity;
        int array_capacity;
        Type *array;
        int ihead;
        int itail;
        int entry_count;
        // other integer member variables, as necessary

    public:
        Dynamic_queue( int = 10 );
        Dynamic_queue( Dynamic_queue const & );
        ~Dynamic_queue();

        Type head() const;
        int size() const;
        bool empty() const;
        int capacity() const;

        void swap( Dynamic_queue & );
        Dynamic_queue &operator=( Dynamic_queue );
        void enqueue( Type const & );
        Type dequeue();
        void clear();

    // Friends

    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Dynamic_queue<T> const & );
};

template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( int n ):
initial_capacity( std::max( n, 1 ) ),
array_capacity( initial_capacity ),
array( new Type[initial_capacity] ),
ihead( 0 ),
itail( initial_capacity - 1 ),
entry_count( 0 ) {
    //set the itail initially to -1
    itail = -1;
}

template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( Dynamic_queue const &queue ):
initial_capacity( queue.initial_capacity ),
array_capacity( queue.array_capacity ),
array( new Type[array_capacity] ),
ihead( queue.ihead ),
itail( queue.itail ),
entry_count( queue.entry_count ) {
    // The above initializations copy the values of the appropriate
    // member variables and allocate memory for the data structure;
    // however, you must still copy the stored objects.

    //loop through the array copying objects into the new array
    for (int i = 0 ; i < entry_count ; i++){
        array[i] = queue.array[i];
    }
}

template <typename Type>
Dynamic_queue<Type>::~Dynamic_queue() {
    //delete the array
    delete [] array;
}

template <typename Type>
int Dynamic_queue<Type>::size() const {
    //return the entry count that shows the size
    return entry_count;
}

template <typename Type>
int Dynamic_queue<Type>::capacity() const {
   
    return array_capacity;
}

template <typename Type>
bool Dynamic_queue<Type>::empty() const {
    // return boolean:True if size is 0
    return(size() == 0);
}

template <typename Type>
Type Dynamic_queue<Type>::head() const {
    //throw exception if queue is empty else return head
    if(empty()){
        throw underflow();
    }
    else {  
        return array[ihead];
    }
}

template <typename Type>
void Dynamic_queue<Type>::swap( Dynamic_queue<Type> &queue ) {
    std::swap( initial_capacity, queue.initial_capacity );
    std::swap( array_capacity, queue.array_capacity );
    std::swap( array, queue.array );
    std::swap( ihead, queue.ihead );
    std::swap( itail, queue.itail );
    std::swap( entry_count, queue.entry_count );
}

template <typename Type>
Dynamic_queue<Type> &Dynamic_queue<Type>::operator=( Dynamic_queue<Type> rhs ) {
    swap( rhs );
    
    return *this;
}

template <typename Type>
void Dynamic_queue<Type>::enqueue( Type const &obj ) {
    // Insert the argument at the tail of the queue. If the array is full before the argument is placed into the queue,
    // the capacity of the array is first doubled.
    if (size() == array_capacity){
        Type *arrayTemp = new Type[array_capacity*2];
        for (int i = 0; i < array_capacity; i++){
            arrayTemp[i] = array[i];
        }
        delete [] array;
        array = arrayTemp;
        array_capacity *= 2;
    }

    if (itail == array_capacity - 1 && size() != array_capacity ) 
    {
        itail = 0;
    }
    itail++;
    array[itail] = obj;
    entry_count++;

}

template <typename Type>
Type Dynamic_queue<Type>::dequeue() {
    //Removes the object at the head of the queue. If, after the object is removed,
    // the array is one-quarter (1/4) full and the array capacity is greater than the initial capacity, 
    //the capacity of the array is halved. This will throw the underflow exception if the queue is empty
    if (empty()){
        throw underflow();
    }

    Type frontEntry = array[ihead];
    ihead++;
    entry_count -= 1;

    if(entry_count*4 <= array_capacity && array_capacity > initial_capacity){
        Type *arrayHalf = new Type[array_capacity/2];
        for (int i = 0; i < array_capacity; i++){
            arrayHalf[i] = array[i];
        }
    
        delete [] array;
        array = arrayHalf;
        array_capacity /= 2;
    }

    return frontEntry;
    

}

template <typename Type>
void Dynamic_queue<Type>::clear() {
    // Enter your implementation here.
}

// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator<<( std::ostream &out, Dynamic_queue<Type> const &queue ) {
    // I don't know how you are implementing your queue so I cannot print it.
    // If you want, you can print whatever you want here and then call cout
    // in the driver.

    // Remember to redirect to out, e.g.,
    //      out << "Hello!";
    for (int i = queue.ihead; i < queue.size(); i++)
    {
        out << queue.array[i] << " " ;
    }

    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif

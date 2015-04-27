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

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
    private:
        Double_node<Type> *list_head;
        Double_node<Type> *list_tail;
        int list_size;

    public:
        Double_sentinel_list();
        Double_sentinel_list( Double_sentinel_list const & );
        ~Double_sentinel_list();

        // Accessors

        int size() const;
        bool empty() const;

        Type front() const;
        Type back() const;

        Double_node<Type> *head() const;
        Double_node<Type> *tail() const;

        int count( Type const & ) const;

        // Mutators

        void swap( Double_sentinel_list & );
        Double_sentinel_list &operator=( Double_sentinel_list const & );

        void push_front( Type const & );
        void push_back( Type const & );

        Type pop_front();
        Type pop_back();

        int erase( Type const & );

    // Friends

    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
    //set sentinel 1 and 2 as list head and tail and ensured theyre pointing to each other 
    list_head = new Double_node<Type>(nullptr, nullptr, list_tail);
    list_tail = new Double_node<Type>(nullptr, list_head, nullptr );
    list_head->next_node = list_tail;  //pointed to nullptr since list_tail wasnt declared

}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ), 
list_tail( nullptr ),
list_size( 0 ) {
    
    // set sentinels as required for an empty list
    list_head = new Double_node<Type>(nullptr, nullptr, list_tail);
    list_tail = new Double_node<Type>(nullptr, list_head, nullptr );
    list_head->next_node = list_tail;
    if(list.empty())
    {
        return;
    }

    //set ptr to first value in list and loop(while copying) until it points to tail
    Double_node<Type> *start = list.head()->next();
    while(start != list.tail()){
        push_back(start->retrieve());
        start = start->next();
    }

}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    // utilise popfront as it deletes the node, then delete both sentinels
    
    while(!empty()){
        pop_front();
    }
    delete list_head;
    delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    return list_size ;
}


//returns true '1' if empty and false '0' if not 
template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    if (list_size == 0){
        return true;
    }
    else {
        return false;
    }
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    // if not empty returns the first value in the list 
    if (empty()){
        throw underflow();
    }
    else{
        return list_head->next()->retrieve();
    }
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    //if not empty returns last value in the list 
    if (empty()){
        throw underflow();
    }
    else{
        return list_tail->previous()->retrieve();
    }

}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {
    return list_head;
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {
    return list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    //set a ptr to the front of the list and let it go through until it either 
    //reaches end of list or finds first object
    int counter = 0;
    Double_node<Type> *start = list_head->next();
    while(start->next_node != nullptr){
    //for (int i = 0; i < list_size; i++){
        if(start->retrieve() == obj ){
            counter += 1;
        }
        start = start->next();
    }
    return counter;
    //return 0;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
    std::swap( list_head, list.list_head );
    std::swap( list_tail, list.list_tail );
    std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> const &rhs ) {
    Double_sentinel_list<Type> copy( rhs );

    swap( copy );
    
    return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
    //created 2 pointers 1 pointing to a new node the other to front of list 
    //set the new node between the head and the front of list by setting ptrs
    //next_node(head) and prev_node(front) to point to the new node as it points back
    Double_node<Type> *pushedFront;
    Double_node<Type> *tempFNode;
    tempFNode = list_head->next();
    pushedFront = new Double_node<Type>(obj, list_head, tempFNode);
    tempFNode->previous_node = pushedFront;
    list_head->next_node = pushedFront;
    pushedFront->next_node = tempFNode;
    pushedFront->previous_node = list_head;
    list_size +=1;
    

}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    //created 2 pointers 1 pointing to a new node the other to back of list 
    //set the new node between the tail and the front of list by setting ptrs
    //next_node(back) and prev_node(tail) to point to the new node as it points back
    Double_node<Type> *pushedBack;
    Double_node<Type> *tempBNode;
    tempBNode = list_tail->previous();
    pushedBack = new Double_node<Type>(obj, tempBNode, list_tail);
    tempBNode->next_node = pushedBack;
    list_tail->previous_node = pushedBack;
    pushedBack->previous_node = tempBNode;
    pushedBack->next_node = list_tail;
    list_size += 1;
    


}

template <typename Type>
Type Double_sentinel_list<Type>::pop_front() {
    //set 2 ptrs, if list isnt empty, to point to 1st and 2nd in the list 
    //set a variable to hold element of 1st node 
    //set nextNode(head) to 2nd and previousNode(2nd) to point to head 
    //deleted the 1st node and reduced list size 

    Type pop;
    Double_node<Type> *popF;
    Double_node<Type> *popFnext;
    if(empty()){
        throw underflow();
    }
    else{
        pop = list_head->next()->retrieve();
        popF = list_head->next();
        popFnext = list_head->next()->next();
        popFnext->previous_node = list_head;
        list_head->next_node = popFnext;
        delete popF;
        popFnext = nullptr;
        list_size -= 1;

    }
            
    return pop;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {
    //set 2 ptrs, if list isnt empty, to point to last and 2nd to last in the list 
    //set a variable to hold element of last node 
    //set nextNode(2nd to last) to tail and previousNode(tail) to point to 2nd to last  
    //deleted the last node and reduced list size
    Type pop;
    Double_node<Type> *popB;
    Double_node<Type> *popBprev;
    if(empty()){
        throw underflow();
    }
    else{
        pop = list_tail->previous()->retrieve();
        popB = list_tail->previous();
        popBprev = list_tail->previous()->previous();
        popBprev->next_node = list_tail;
        list_tail->previous_node = popBprev;
        delete popB;
        popBprev = nullptr;
        list_size -= 1;

    }
            
    return pop;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    // set ptr to iterate through list using while loop and delete the 1st node with 
    //specified element if it at all is in the list and return if you got any(1) or not(0)  

    int counter = 0;
    Double_node<Type> *start = list_head->next();
    Double_node<Type> *b_start;
    Double_node<Type> *a_start;
    while(start->next_node != nullptr){

        b_start = start->previous();
        a_start = start->next();
        if(start->retrieve() == obj ){
            delete start;
            counter += 1;
            list_size -= 1;
            b_start->next_node = a_start;
            a_start->previous_node = b_start;
            break;
        }
        start = start->next();
    }
    start = nullptr;
    b_start = nullptr;
    a_start = nullptr;

    return counter;

}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
    out << "head";

    for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
        if ( ptr == list.head() || ptr == list.tail() ) {
            out << "->S";
        } else {
            out << "->" << ptr->retrieve();
        }
    }

    out << "->0" << std::endl << "tail";

    for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
        if ( ptr == list.head() || ptr == list.tail() ) {
            out << "->S";
        } else {
            out << "->" << ptr->retrieve();
        }
    }

    out << "->0";

    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif

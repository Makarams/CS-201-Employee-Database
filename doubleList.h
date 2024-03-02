#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include<iostream>
#include "doubleNode.h"
using namespace std;

template<class T>
class doubleList {
private:
    doubleNode<T>* list_head, * list_tail;  // Pointer to the head and tail node
    int len = 0;    // The current size of the list
public:
    doubleList() {}      // I\nitializing an object with no parameter
    doubleList(const doubleList<T>& temp);    // Initializing an object with the parameter of the object type
    ~doubleList();     // Destructor for deleting the pointer in the list
    int size() const;      // Return the size of the list
    bool empty() const;      // Return true if the list is emtpy and false otherwise
    T front() const;    // Returning the data of the head node
    T back() const;     // Returning the data of the tail node
    doubleNode<T>* head() const;   // Returning a pointer of the head node
    doubleNode<T>* tail() const;   // Returning a pointer of the tail node
    int count(T) const;     // return the number of node that has that value
    void displayList() const;       // displaying the list from head to tail
    void displayListReverse() const;    // displaing the list from tail to head
    void push_back(T value);        // adding a node at the back of the linked list
    void pop_front();       // removing the first node in the linked list
    void swap(int, int);
    bool erase(const T&);   // remove the first node that has the same value as the parameter 
    void setHead(doubleNode<T>*);
    void setTail(doubleNode<T>*);
    void clear();
    T valueAt(int);
    template<class E>
    friend ostream& operator<<(ostream& os, doubleList<E>& list);      // displaing the list from head to tail
};

template<class T>
doubleList<T>::doubleList(const doubleList<T>& temp) {       // constructor for copying the linked list
    doubleNode<T>* tem = new doubleNode<T>;   // creating a new pointer object
    tem = temp.head();      // assigning the pointer object to the argument
    while (tem) {
        push_back(tem->getData());       // adding the node value of the pointer to the new create object
        tem = tem->getNext();        // iterating through the linked list
    }
}

template<class T>
doubleList<T>::~doubleList() { clear(); }    // poping every node untill the list is empty

template<class T>
int doubleList<T>::size() const { return this->len; }      // return the current length of the list

template<class T>
bool doubleList<T>::empty() const { return size() == 0; }     // return true if the list is empty and false otherwise

template<class T>
T doubleList<T>::front() const {       // returning the value of the first node
    return list_head->getData();
}

template<class T>
T doubleList<T>::back() const {        // returning the value of the last node
    return list_tail->getData();
}

template<class T>
doubleNode<T>* doubleList<T>::head() const { return list_head; }  // returning a pointer to the first node in the list

template<class T>
doubleNode<T>* doubleList<T>::tail() const { return list_tail; }  // returning a pointer to the last node in the list

template<class T>
int doubleList<T>::count(T value) const {      // return the number of node that has that value
    if (empty()) return 0;      // return 0 if the current list is empty
    int ctr = 0;        // create a variable to store the number node that has its data equal the value
    doubleNode<T>* temp = new doubleNode<T>;      // creating a pointer to iterate through the linked list
    temp = head();      // assigning the pointer to the head of the list
    while (temp) {
        if (temp->getData() == value) ctr++;     // if the node's data has the same value it will increment the ctr
        temp = temp->getNext();      // moving to the next node
    }
    return ctr;
}

template<class T>
void doubleList<T>::displayList() const {      // displaying the list from head to tail
    if (empty()) return;    // end the function if the list is empty
    int ctr = 1;
    doubleNode<T>* temp = head();  // assigning the pointer to the head of the list
    cout << "(" << ctr++ << ") " << temp->getData();    // print the current node with the data
    temp = temp->getNext(); // Iterate to the next node
    while (temp) {
        cout << " ==> (" << ctr++ << ") " << temp->getData();   // print the current node with the data
        temp = temp->getNext();      // iterating through the list
    }
    cout << endl;   // End the current line
}

template<class T>
void doubleList<T>::displayListReverse() const {   // displaying the list from tail to head
    if (empty()) return;    // end the function if the list is empty
    int ctr = size();
    doubleNode<T>* temp = tail();      // assigning the pointer to the tail of the list
    cout << "(" << ctr-- << ") " << temp->getData();    // print the current node with the data
    temp = temp->getPrev();     // go the previous node
    while (temp) {
        cout << " <== (" << ctr-- << ") " << temp->getData();       // print the current node with the data
        temp = temp->getPrev();      // iterating through the list
    }
    cout << endl;       // End the current line
}

template<class T>
void doubleList<T>::push_back(T value) {    // adding a node at the back of the linked list
    doubleNode<T>* temp = new doubleNode<T>;      // creating a new pointer object of the class node
    temp->setData(value);         // giving the pointer node's data to the value
    if (empty()) list_head = list_tail = temp;      // if the list is empty the list_head and list_tail is assign to the pointer temp
    else {
        list_tail->setNext(temp);         // assigning the current list_tail next pointer to the temp pointer
        temp->setPrev(list_tail);     // assigning the temp prev pointer to the temp
        list_tail = temp;       // changing the list_tail pointer to the temp pointer
        list_tail->setData(value);      // set the curent list tail value equal to value
    }
    cout << value << " has been added" << endl;     // display the value of the current list_tail
    len++;      // increment the size of the list
}

template<class T>
void doubleList<T>::pop_front() {      // removing the first node in the linked list
    if (empty()) {
        return;     // exit the function if the list is empty
    }
    if (size() == 1) {      // if the size of the list equal to 1 then set the list_head and list_tail to null
        list_head = list_tail = nullptr;    
        len--;      // len is now equal to 0    
        return; // exit the function
    }
    doubleNode<T>* temp = head();      // assigning the new pointer node object to the head
    list_head = temp->getNext();     // moving the list_head pointer to next pointer
    delete list_head->getPrev();   // deleting all the data at the prev
    list_head->setPrev(nullptr);     // assigning the prev pointer of the current list_head to NULL
    len--;          // decrement the list size
    return;
}

template<class T>
void doubleList<T>::swap(int first, int second) {       // This method takes two parameter which is the location of the two node to be swap
    // If any of the condition is met the function exits
    if (min(first, second) <= 0 || first == second || max(first, second) > size()) return;

    doubleNode<T>* node1 = new doubleNode<T>;   // for storing the first node data
    doubleNode<T>* node2 = new doubleNode<T>;   // for storing the second node data

    doubleNode<T>* iterate = new doubleNode<T>;     // used for iterating through the list
    iterate = head();       // set the starting index at the head
    int ctr = 1;   
    while (iterate) {
        // Setting the first node to the iterate
        if (ctr == first) node1 = iterate;
        // Setting the second node to the iterate
        if (ctr == second) node2 = iterate;

        ctr++;  // Increment the counter
        iterate = iterate->getNext();   // moving the iterate to the next node
    }

    // Swapping the data with a temp variable
    T temp = node1->getData();
    node1->setData(node2->getData());
    node2->setData(temp);
}

template<class T>
bool doubleList<T>::erase(const T& value) {    // remove the first node that has the same value as the parameter 
    if (empty()) {          // if the list is emtpy the function exit
        return false;
    }
    if (head()->getData() == value) {        // if the head data has the same value it will use the function pop_front() to remove the node
        pop_front();      // display the value that has been removed
        return true;     // exit the function
    }

    doubleNode<T>* temp = new doubleNode<T>;      // creating a new pointer for iterating and deleting the node data at the temp location
    temp = head()->getNext();     // assigning the temp value equal to the next node after the head pointer
    while (temp) {      // iterating through the list
        if (temp->getData() == value) {      // if the temp data is equal to the value this block is executed
            doubleNode<T>* first, * second;        // creating two pointer for the node after and before the current temp node
            first = second = new doubleNode<T>;
            first = temp->getPrev();     // assigning the first node to the previous temp node
            second = temp->getNext();    // assigning the second node to the next temp node

            first->setNext(second);     // changing the first node next pointer to the location of the second node
            second->setPrev(first);      // changing the second node prev pointer to the location of the first node
            len--;          // decrement the list size
            delete temp;       // delete all the data at the temp location 
            return 1;     // exit the function
        }
        temp = temp->getNext();      // moving temp to the next node
    }
    return 0;
}
template<class T>
void doubleList<T>::setHead(doubleNode<T>* head) {
    list_head = head;       
}
template<class T>
void doubleList<T>::setTail(doubleNode<T>* tail) {
    list_tail = tail;
}
template<class T>
void doubleList<T>::clear() {   // clear all the node untill it is empty
    while (!empty()) pop_front();
}
template<class E>
ostream& operator<<(ostream& os, doubleList<E>& list) {        // can be use to cout << list;
    list.displayList();         // will display the list from head to tail
    return os;      // a return function of the ostream
}
template<class T>
T doubleList<T>::valueAt(int at) {
    if (at < 1 or at > len) {
        cout << "Index out of bound" << endl;
        system("pause");
        exit(0);
    }
    int ctr = 1;
    doubleNode<T>* temp = new doubleNode<T>;
    temp = head();
    while (temp) {
        if (ctr++ == at) {
            return temp->getData();
        }
        temp = temp->getNext();
    }
}

#endif //DOUBLE_LIST_H

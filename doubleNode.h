#pragma once
#ifndef DOUBLENODE_H
#define DOUBLENODE_H // Defining a definition for a header file

/**
 *	This class is created is to store data
 * 	of each node including a next and prev
 * 	pointer for pointing to the next node
 * 	inside a double linked list.
 */
template <class T> class doubleNode {
public:
	doubleNode();      // A constructor for initialization of an object
	T getData() const; // Method used for retrieving data of the current node
	void setData(T);   // Method used for modifying the data of the current node
	doubleNode<T>* getNext() const; // Method used for retreving the next node
	doubleNode<T>* getPrev() const; // Method used for retreving the prev node
	void setNext(doubleNode<T>*);  // Method used for modifying the next pointer
	void setPrev(doubleNode<T>*);  // Method used for modifying the prev pointer

private:
	T data;
	doubleNode<T>* next, * prev;
};

template <class T>
doubleNode<T>::doubleNode(): next(nullptr), prev(nullptr) {} // Setting the next and prev pointer to be a nullptr
template <class T> T doubleNode<T>::getData() const { return this->data; }
template <class T> void doubleNode<T>::setData(T data) { this->data = data; }
template <class T> void doubleNode<T>::setNext(doubleNode<T>* next) {
	this->next = next;
}
template <class T> void doubleNode<T>::setPrev(doubleNode<T>* prev) {
	this->prev = prev;
}
template <class T> doubleNode<T>* doubleNode<T>::getNext() const {
	return this->next;
}
template <class T> doubleNode<T>* doubleNode<T>::getPrev() const {
	return this->prev;
}

#endif
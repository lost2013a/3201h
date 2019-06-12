#ifndef NODE_HPP
#define NODE_HPP

#include <stdio.h>

template <typename T> class node {
public:
	T nodeValue;      // data held by the node
	node<T> *next;    // next node in the list

	// default constructor with no initial value
	node() : next(NULL) {}

	// constructor. initialize nodeValue and next
	node(const T& item, node<T> *nextNode = NULL) : nodeValue(item), next(nextNode) {}
};

template <typename T> class dnode {
public:
	// the members of a dnode object are used for operations within a
	// doubly linked list; access is simplified by making them public

	T nodeValue;    // data value of the node
	dnode<T> *prev;	// previous node in the list
	dnode<T> *next;	// next node in the list

	// default constructor. creates object with value T(), the
	// default value of type T. set the node pointers to point at
	// the node itself
	dnode() {
		next = this;	// the next node is the current node
		prev = this;	// the previous node is the current node
	}

	// constructor with an argument to initialize nodeValue.
	// set the node pointers to point at the node itself
	dnode(const T& value): nodeValue(value) {
		next = this;	// the next node is the current node
		prev = this;	// the previous node is the current node
	}
};

template <typename T> class stnode {
public:
	// stnode is used to implement the binary search tree class
	// making the data public simplifies building the class functions

	T nodeValue;
	stnode<T> *left, *right, *parent;
	// child pointers and pointer to the node's parent

	stnode (const T& item, stnode<T> *lptr = NULL, stnode<T> *rptr = NULL, stnode<T> *pptr = NULL):
		nodeValue(item), left(lptr), right(rptr), parent(pptr) {}
};
#endif


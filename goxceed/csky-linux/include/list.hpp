#ifndef LIST_CLASS
#define LIST_CLASS

#include "node.hpp"
#include "except.hpp"

namespace gx {
template <typename T> class list {
public:
#include "liter.inl"
	list();
	list(int n, const T& item = T());
	list(T* first, T* last);
	list(const list<T>& obj);

	~list();

	// overloaded assignment operator
	list<T>& operator= (const list<T>& rhs);

	int size() const { return listSize;}
	bool empty() const { return listSize == 0; }

	// insert item at the front of the list
	// Postcondition: the list size increases by 1
	void push_front(const T& item);

	// insert item at the back of the list
	// Postcondition: the list size increases by 1
	void push_back(const T& item);

	// insert item before pos.
	// Postcondition: the list size increases by 1
	iterator insert(iterator pos, const T& item);

	// erase the front of the list.
	// Precondition: the list is not empty. if the list is
	// empty, the function throws the underflowError exception.
	// Postcondition: the list size decreases by 1

	void pop_front();
	// erase the back of the list.
	// Precondition: the list is not empty. if the list is
	// empty, the function throws the underflowError exception.
	// Postcondition: the list size decreases by 1

	void pop_back();
	// erase the list element at pos
	// Precondition: the list is not empty. if the list is
	// empty, the function throws the underflowError exception.
	// Postcondition: the list size decreases by 1
	void erase(iterator pos);

	// return a reference to the value at the front of the list.
	// Precondition: the list is not empty. if the list is
	// empty, the function throws the underflowError exception
	T& front();
	const T& front() const;

	// constant version of front()
	// return a reference to the value at the back of the list.
	// Precondition: the list is not empty. if the list is
	// empty, the function throws the underflowError exception
	T& back();

	// constant version of back()
	const T& back() const;

	iterator begin()             { return iterator(header->next); }
	const_iterator begin() const { return const_iterator(header->next); }

	iterator end()               { return iterator(header); }
	const_iterator end() const   { return const_iterator(header); }

private:
	dnode<T> *header;
	// header (sentinel) node

	int listSize;
	// number of elements in the list

	// allocate a dnode object with the value item and
	// return a pointer to it. throw the memoryAllocationError
	// exception of the memory allocation fails
	dnode<T> *getDNode(const T& item);

	// insert item before node curr of the linked list and
	// return the address of the new node
	dnode<T> *dinsert(dnode<T> *curr, const T& item);

	// erase node curr from the linked list.
	// Precondition: the list is not empty. the functions that
	// call derase() check the precondition
	void derase(dnode<T> *curr);
};

template <typename T>
dnode<T> *list<T>::getDNode(const T& item)
{
	dnode<T> *newNode;

	newNode = new dnode<T>(item);
	if (newNode == NULL)
		throw memoryAllocationError("list(): memory allocation failure");

	return newNode;
}

template <typename T>
dnode<T> *list<T>::dinsert(dnode<T> *curr, const T& item)
{
	dnode<T> *newNode = getDNode(item);

	newNode->prev = curr->prev;
	newNode->next = curr;
	curr->prev->next = newNode;
	curr->prev = newNode;

	return newNode;
}

template <typename T>
void list<T>::derase(dnode<T> *curr)
{
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;

	delete curr;
}

// list size is 0
template <typename T>
list<T>::list(): listSize(0)
{
	header = new dnode<T>;
	if (header == NULL)
		throw memoryAllocationError("list(): memory allocation failure");
}

// list size is n
template <typename T>
list<T>::list(int n, const T& value): listSize(n)
{
	header = new dnode<T>;
	if (header == NULL)
		throw memoryAllocationError("list(): memory allocation failure");

	for (int i = 0; i < n; i++)
		dinsert(header->next, value);
}

template <typename T>
list<T>::list(T* first, T* last): listSize(0)
{
	T *curr = first;

	header = new dnode<T>;
	if (header == NULL)
		throw memoryAllocationError("list(): memory allocation failure");

	while (curr != last) {
		dinsert(header, *curr);
		curr++;
		listSize++;
	}
}

template <typename T>
list<T>::list(const list<T>& obj): listSize(obj.listSize)
{
	dnode<T> *curr = obj.header->next, *end = obj.header;

	header = new dnode<T>;
	if (header == NULL)
		throw memoryAllocationError("list(): memory allocation failure");

	while (curr != end) {
		dinsert(header, curr->nodeValue);
		curr = curr->next;
	}
}

template <typename T>
list<T>::~list()
{
	while (header->next != header)
		derase(header->next);

	listSize = 0;

	delete header;
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& rhs)
{
	dnode<T> *curr = rhs.header->next, *end = rhs.header;

	if (this == &rhs)
		return *this;

	while (header->next != header)
		derase(header->next);

	while (curr != end) {
		dinsert(header, curr->nodeValue);
		curr = curr->next;
	}

	listSize = rhs.listSize;

	return *this;
}

template <typename T>
void list<T>::push_front(const T& item)
{
	dinsert(header->next, item);
	listSize++;
}

template <typename T>
void list<T>::push_back(const T& item)
{
	dinsert(header, item);
	listSize++;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T& item)
{
	dnode<T> *curr = pos.nodePtr, *newNode;

	newNode = dinsert(curr, item);
	listSize++;

	return iterator(newNode);
}


template <typename T>
void list<T>::pop_front()
{
	if (listSize == 0)
		throw underflowError("list pop_front(): list is empty");

	derase(header->next);
	listSize--;
}

template <typename T>
void list<T>::pop_back()
{
	if (listSize == 0)
		throw underflowError("list pop_back(): list is empty");

	derase(header->prev);
	listSize--;
}

template <typename T>
void list<T>::erase(iterator pos)
{
	if (listSize == 0)
		throw underflowError("list erase(): list is empty");

	dnode<T> *curr = pos.nodePtr;

	derase(curr);
	listSize--;
}

template <typename T>
T& list<T>::front()
{
	if (listSize == 0)
		throw underflowError("list front(): list is empty");

	return header->next->nodeValue;
}

template <typename T>
const T& list<T>::front() const
{
	if (listSize == 0)
		throw underflowError("list front(): list is empty");

	return header->next->nodeValue;
}

template <typename T>
T& list<T>::back()
{
	if (listSize == 0)
		throw underflowError("list back(): list is empty");

	return header->prev->nodeValue;
}

template <typename T>
const T& list<T>::back() const
{
	if (listSize == 0)
		throw underflowError("list back(): list is empty");

	return header->prev->nodeValue;
}

};

#endif


#ifndef MINI_VECTOR
#define MINI_VECTOR

#include "except.hpp"

namespace gx {

template <typename T> class vector {
public:
	vector(size_t size = 0);

	vector(const vector<T>& obj);

	~vector();

	typedef T* iterator;
	iterator begin() const { return vArr; }
	iterator end() const   { return vArr + vSize; }

	// assignment operator.
	// Postcondition: current vector holds the same data as rhs
	vector& operator= (const vector<T>& rhs);

	// return the element at the rear of the vector.
	// Precondition: the vector is not empty. if vector
	// is empty, throws the underflowError exception
	T& back();

	// const version used when vector object is a constant
	const T& back() const;

	// provides general access to elements using an index.
	// Precondition: 0 <= i < vSize. if the index is out
	// of range, throws the indexRangeError exception
	T& operator[] (size_t i);

	// const version used when vector object is a constant
	const T& operator[] (size_t i) const;

	// insert item at the rear of the vector.
	// Postcondition: the vector size is increased by 1
	void push_back(const T& item);
	iterator erase(iterator position) {
		while (position != end()) {
			*position = *(position + 1);
			position++;
		}
		vSize -= 1;
		return position + 1;
	}

	void assign(iterator first, iterator last);
	//void assign(size_t n, const T& val);

	// remove element at the rear of the vector.
	// Precondition: vector is not empty. if the vector is
	// empty, throws the underflowError exception
	void pop_back();

	size_t size() const     { return vSize;                }
	bool   empty() const    { return vSize == 0;           }
	size_t capacity() const { return vCapacity;            }
	void   resize(size_t n) { vSize = n; reserve(n, true); }
	void   clear()          { resize(0);                   }
private:
	size_t vCapacity; // amount of available space
	size_t vSize;     // number of elements in the list
	T *vArr;          // the dynamic array

	// called by public functions only if n > vCapacity. expands
	// the vector capacity to n elements, copies the existing
	// elements to the new space if copy == true, and deletes
	// the old dynamic array. throws the memoryAllocationError
	// exception if memory allocation fails
	void reserve(size_t n, bool copy);
};

template <typename T>
void vector<T>::reserve(size_t n, bool copy)
{
	T *newArr;

	newArr = new T[n];
	if (newArr == NULL)
		throw memoryAllocationError("vector reserve(): memory allocation failure");

	if (copy) {
		for (size_t i = 0; i < vSize; i++)
			newArr[i] = vArr[i];
	}

	if (vArr != NULL)
		delete [] vArr;

	vArr = newArr;
	vCapacity = n;
}

// constructor. initialize vSize and vCapacity.
// allocate a dynamic array of vSize integers
// and initialize the array with T()
template <typename T>
vector<T>::vector(size_t size): vCapacity(0), vSize(0), vArr(NULL)
{
	if (size == 0)
		return;

	reserve(size, false);
	vSize = size;

	for (size_t i = 0; i < vSize; i++)
		vArr[i] = T();
}

// copy constructor. make the current object a copy of obj.
// for starters, use initialization list to create an empty vector
template <typename T>
vector<T>::vector(const vector<T>& obj): vCapacity(0), vSize(0), vArr(NULL)
{
	if (obj.vSize == 0)
		return;

	reserve(obj.vSize, false);
	vSize = obj.vSize;

	for (size_t i = 0; i < vSize; i++)
		vArr[i] = obj.vArr[i];
}

template <typename T>
vector<T>::~vector()
{
	if (vArr != NULL)
		delete [] vArr;
}

// replace existing object (left-hand operand) by rhs (right-hand operand)
template <typename T>
vector<T>& vector<T>::operator= (const vector<T>& rhs)
{
	if (vCapacity < rhs.vSize)
		reserve(rhs.vSize, false);

	vSize = rhs.vSize;

	for (size_t i = 0; i < vSize; i++)
		vArr[i] = rhs.vArr[i];

	return *this;
}

// check vSize and throw an underflowError exception if the
// value is 0; otherwise return the element vArr[vSize-1]
template <typename T>
T& vector<T>::back()
{
	if (vSize == 0)
		throw underflowError("vector back(): vector empty");

	return vArr[vSize-1];
}

template <typename T>
const T& vector<T>::back() const
{
	if (vSize == 0)
		throw underflowError("vector back(): vector empty");

	return vArr[vSize-1];
}

// provides general access to array elements
template <typename T>
T& vector<T>::operator[] (size_t i)
{
	if (i < 0 || i >= vSize)
		throw indexRangeError("vector: index range error", i, vSize);

	return vArr[i];
}

// provides general access to array elements. constant version
template <typename T>
const T& vector<T>::operator[] (size_t i) const
{
	if (i < 0 || i >= vSize)
		throw indexRangeError("vector: index range error", i, vSize);

	return vArr[i];
}

template <typename T>
void vector<T>::push_back(const T& item)
{
	T newValue = item;

	if (vSize == vCapacity) {
		if (vCapacity == 0)
			reserve(1, false);
		else
			reserve(2 * vCapacity, true);
	}

	vArr[vSize] = newValue;
	vSize++;
}

template <typename T>
void vector<T>::pop_back()
{
	if (vSize == 0)
		throw underflowError("vector pop_back(): vector is empty");

	vSize--;
}

template <typename T>
void vector<T>::assign(iterator first, iterator last)
{
	while (first < last) {
		push_back(*(first++));
	}
}
#if 0
template <typename T>
void vector<T>::assign(size_t n, const T& val)
{
	for (size_t i = 0; i < n; i++)
		push_back(val);
}
#endif
};

#endif

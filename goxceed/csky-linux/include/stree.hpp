#ifndef BINARY_SEARCH_TREE_CLASS
#define BINARY_SEARCH_TREE_CLASS

#include <stdio.h>

#include "node.hpp"
#include "except.hpp"
#include "list.hpp"
#include "pair.hpp"

namespace gx {

template <typename T> class stree {
public:
// include the iterator nested classes
#include "stiter.inl"

	stree();
	stree(T *first, T *last);
	stree(const stree<T>& tree);
	~stree();
	stree<T>& operator= (const stree<T>& rhs);

	// search for item. if found, return an iterator pointing at it in the tree; otherwise, return end()
	iterator find(const T& item) {
		stnode<T> *curr = findNode(item);

		return curr != NULL ? iterator(curr, this) : end();
	}

	const_iterator find(const T& item) const {
		stnode<T> *curr = findNode(item);

		return curr != NULL ?  const_iterator(curr, this) : end();
	}

	int empty() const;
	int size() const;

	// if item is not in the tree, insert it and return a pair whose iterator component points
	// at item and whose bool component is true. if item is in the tree, return a pair whose iterator
	// component points at the existing item and whose bool component is false
	// Postcondition: the tree size increases by 1 if item is not in the tree
	pair<iterator, bool> insert(const T& item) {
		stnode<T> *t = root, *parent = NULL, *newNode;

		while(t != NULL) {
			parent = t;
			if (item == t->nodeValue)
				return pair<iterator, bool> (iterator(t, this), false);
			else if (item < t->nodeValue)
				t = t->left;
			else
				t = t->right;
		}

		newNode = getSTNode(item,NULL,NULL,parent);

		if (parent == NULL)
			root = newNode;
		else if (item < parent->nodeValue)
			parent->left = newNode;
		else
			parent->right = newNode;

		treeSize++;

		return pair<iterator, bool> (iterator(newNode, this), true);
	}

	// if item is in the tree, erase it and return 1;
	// otherwise, return 0
	// Postcondition: the tree size decreases by 1 if
	// item is in the tree
	int erase(const T& item);

	// erase the item pointed to by pos.
	// Preconditions: the tree is not empty and pos points
	// to an item in the tree. if the tree is empty, the
	// function throws the underflowError exception. if the
	// iterator is invalid, the function throws the referenceError
	// exception.
	// Postcondition: the tree size decreases by 1
	void erase(iterator pos);

	// erase all items in the range [first, last).
	// Precondition: the tree is not empty. if the tree
	// is empty, the function throws the underflowError
	// exception.
	// Postcondition: the size of the tree decreases by
	// the number of elements in the range [first, last)
	void erase(iterator first, iterator last);

	// return an iterator pointing to the first item inorder
	iterator begin() {
		stnode<T> *curr = root;

		// if the tree is not empty, the first node
		// inorder is the farthest node left from root
		if (curr != NULL)
			while (curr->left != NULL)
				curr = curr->left;

		return iterator(curr, this);
	}

	const_iterator begin() const {
		const stnode<T> *curr = root;

		// if the tree is not empty, the first node
		// inorder is the farthest node left from root
		if (curr != NULL)
			while (curr->left != NULL)
				curr = curr->left;

		return const_iterator(curr, this);
	}

	// return an iterator pointing just past the end of the tree data
	iterator end() {
		return iterator(NULL, this);
	}

	const_iterator end() const {
		return const_iterator(NULL, this);
	}

private:
	// pointer to tree root
	stnode<T> *root;

	// number of elements in the tree
	int treeSize;

	// allocate a new tree node and return a pointer to it.
	// if memory allocation fails, the function throws the
	// memoryAllocationError exception
	stnode<T> *getSTNode(const T& item, stnode<T> *lptr,stnode<T> *rptr, stnode<T> *pptr);

	// recursive function used by copy constructor and assignment
	// operator to assign the current tree as a copy of another tree
	stnode<T> *copyTree(stnode<T> *t);

	// recursive function used by destructor and assignment
	// operator to delete all the nodes in the tree
	void deleteTree(stnode<T> *t);

	// search for item in the tree. if it is in the tree,
	// return a pointer to its node; otherwise, return NULL.
	// used by find() and erase()
	stnode<T> *findNode(const T& item) const;
};

template <typename T> stnode<T> *stree<T>::getSTNode(const T& item,
		stnode<T> *lptr,stnode<T> *rptr, stnode<T> *pptr)
{
	stnode<T> *newNode;

	// initialize the data and all pointers
	newNode = new stnode<T> (item, lptr, rptr, pptr);
	if (newNode == NULL)
		throw memoryAllocationError("stree: memory allocation failure");

	return newNode;
}

template <typename T> stnode<T> *stree<T>::copyTree(stnode<T> *t)
{
	stnode<T> *newlptr, *newrptr, *newNode;

	if (t == NULL)
		return NULL;

	// copy the left branch of root t and assign its root to newlptr
	newlptr = copyTree(t->left);

	// copy the right branch of tree t and assign its root to newrptr
	newrptr = copyTree(t->right);

	// allocate storage for the current root node, assign
	// its value and pointers to its left and right subtrees.
	// the parent pointer of newNode is assigned when
	// newNode's parent is created. if newNode is root,
	// NULL is the correct value for its parent pointer
	newNode = getSTNode(t->nodeValue, newlptr, newrptr, NULL);

	// the current node is the parent of any subtree that is not empty
	if (newlptr != NULL)
		newlptr->parent = newNode;
	if (newrptr != NULL)
		newrptr->parent = newNode;

	return newNode;
}

// delete the tree stored by the current object
template <typename T>
void stree<T>::deleteTree(stnode<T> *t)
{
	// if current root node is not NULL, delete its left subtree,
	// its right subtree and then the node itself
	if (t != NULL)
	{
		deleteTree(t->left);
		deleteTree(t->right);
		delete t;
	}
}

// search for data item in the tree. if found, return its node
// address; otherwise, return NULL
template <typename T>
stnode<T> *stree<T>::findNode(const T& item) const
{
	// cycle t through the tree starting with root
	stnode<T> *t = root;

	// terminate on on empty subtree
	while(t != NULL && !(item == t->nodeValue))
		if (item < t->nodeValue)
			t = t->left;
		else
			t = t->right;

	return t;
}

template <typename T>
stree<T>::stree(): root(NULL),treeSize(0) {}

template <typename T>
stree<T>::stree(T *first, T *last): root(NULL),treeSize(0)
{
	T *p = first;

	while (p != last) {
		insert(*p);
		p++;
	}
}

template <typename T>
stree<T>::stree(const stree<T>& tree): treeSize(tree.treeSize)
{
	root = copyTree(tree.root);
}

template <typename T>
stree<T>::~stree()
{
	deleteTree(root);

	root = NULL;
	treeSize = 0;
}

template <typename T>
stree<T>& stree<T>::operator= (const stree<T>& rhs)
{
	if (this == &rhs)
		return *this;

	deleteTree(root);

	root = copyTree(rhs.root);

	treeSize = rhs.treeSize;

	return *this;
}

template <typename T>
int stree<T>::empty() const
{
	return root == NULL;
}

template <typename T>
int stree<T>::size() const
{
	return treeSize;
}

template <typename T>
void stree<T>::erase(iterator pos)
{
	// dNodePtr = pointer to node D that is deleted
	// pNodePtr = pointer to parent P of node D
	// rNodePtr = pointer to node R that replaces D
	stnode<T> *dNodePtr = pos.nodePtr, *pNodePtr, *rNodePtr;

	if (treeSize == 0)
		throw underflowError("stree erase(): tree is empty");

	if (dNodePtr == NULL)
		throw referenceError("stree erase(): invalid iterator");

	// assign pNodePtr the address of P
	pNodePtr = dNodePtr->parent;

	// If D has a NULL pointer, the
	// replacement node is the other child
	if (dNodePtr->left == NULL || dNodePtr->right == NULL) {
		if (dNodePtr->right == NULL)
			rNodePtr = dNodePtr->left;
		else
			rNodePtr = dNodePtr->right;

		if (rNodePtr != NULL)
			// the parent of R is now the parent of D
			rNodePtr->parent = pNodePtr;
	}
	// both pointers of dNodePtr are non-NULL.
	else {
		// find and unlink replacement node for D.
		// starting at the right child of node D,
		// find the node whose value is the smallest of all
		// nodes whose values are greater than the value in D.
		// unlink the node from the tree.

		// pOfRNodePtr = pointer to parent of replacement node
		stnode<T> *pOfRNodePtr = dNodePtr;

		// first possible replacement is right child of D
		rNodePtr = dNodePtr->right;

		// descend down left subtree of the right child of D,
		// keeping a record of current node and its parent.
		// when we stop, we have found the replacement
		while(rNodePtr->left != NULL) {
			pOfRNodePtr = rNodePtr;
			rNodePtr = rNodePtr->left;
		}

		if (pOfRNodePtr == dNodePtr) {
			// right child of deleted node is the replacement.
			// assign left subtree of D to left subtree of R
			rNodePtr->left = dNodePtr->left;
			// assign the parent of D as the parent of R
			rNodePtr->parent = pNodePtr;
			// assign the left child of D to have parent R
			dNodePtr->left->parent = rNodePtr;
		}
		else {
			// we moved at least one node down a left branch
			// of the right child of D. unlink R from tree by
			// assigning its right subtree as the left child of
			// the parent of R
			pOfRNodePtr->left = rNodePtr->right;

			// the parent of the right child of R is the
			// parent of R
			if (rNodePtr->right != NULL)
				rNodePtr->right->parent = pOfRNodePtr;

			// put replacement node in place of dNodePtr
			// assign children of R to be those of D
			rNodePtr->left = dNodePtr->left;
			rNodePtr->right = dNodePtr->right;
			// assign the parent of R to be the parent of D
			rNodePtr->parent = pNodePtr;
			// assign the parent pointer in the children
			// of R to point at R
			rNodePtr->left->parent = rNodePtr;
			rNodePtr->right->parent = rNodePtr;
		}
	}

	// complete the link to the parent node.

	// deleting the root node. assign new root
	if (pNodePtr == NULL)
		root = rNodePtr;
	// attach R to the correct branch of P
	else if (dNodePtr->nodeValue < pNodePtr->nodeValue)
		pNodePtr->left = rNodePtr;
	else
		pNodePtr->right = rNodePtr;

	// delete the node from memory and decrement tree size
	delete dNodePtr;
	treeSize--;
}

template <typename T>
int stree<T>::erase(const T& item)
{
	int numberErased = 1;
	stnode<T> *p = findNode(item);

	if (p != NULL)
		erase(iterator(p,this));
	else
		numberErased = 0;

	return numberErased;
}

template <typename T>
void stree<T>::erase(iterator first, iterator last)
{
	if (treeSize == 0)
		throw underflowError("stree erase(): tree is empty");

	iterator p = first;

	if (first == begin() && last == end()) {
		// we are asked to erase the entire tree.
		// erase the tree nodes from memory
		deleteTree(root);

		// tree is emtpy
		root = NULL;
		treeSize = 0;
	}
	else {
		// erase each item in a subrange of the tree
		while (p != last)
			erase(p++);
	}
}

}
#endif

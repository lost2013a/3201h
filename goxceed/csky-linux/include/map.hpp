#ifndef MINIMAP_CLASS
#define MINIMAP_CLASS

#include "pair.hpp"
#include "stree.hpp"
#include "string.hpp"

namespace gx {

template <typename Key, typename T> class map {
public:
	typedef pair<const Key, T> value_type;
	typedef typename stree<value_type>::iterator iterator;
	typedef typename stree<value_type>::const_iterator const_iterator;

	map() {}

	map(value_type *first, value_type *last): t(first, last) {}

	bool empty() const              { return t.empty(); }
	int size() const                { return t.size(); }
	int count(const Key& key) const { return t.count(value_type(key, T())); }

	iterator find(const Key& key)              { return t.find(value_type(key, T())); }
	const_iterator find (const Key& key) const { return t.find(value_type(key, T())); }

	// if no value is associated with key, create a new map entry with
	// the default value T() and return a reference to the default value;
	// otherwise, return a reference to the value already associated with the key
	T& operator[] (const Key& key) {
		value_type tmp(key, T());
		iterator iter = t.insert(tmp).first;

		return (*iter).second;
	}

	// if the map does not contain a key/value pair whose
	// key matches that of kvpair, insert a coy of kvpair
	// and return a pair object whose first element is an
	// iterator positioned at the new key/value pair and whose second
	// element is true. if the map already contains a key/value
	// pair whose key matches that of kvpair, return a pair
	// object whose first element is an iterator positioned at the
	// existing key/value pair and whose second element is false
	pair<iterator,bool> insert(const value_type& kvpair) {
		pair<iterator, bool> p = t.insert(kvpair);

		return pair<iterator, bool>(p.first, p.second);
	}

	// erase the key/value pair with the specified key
	// from the map and return the number of items erased (1 or 0)
	int  erase(const Key& key)                { return t.erase(value_type(key, T())); }
	void erase(iterator pos)                  { t.erase(pos);                         }
	void erase(iterator first, iterator last) { t.erase(first,last);                  }
	void clear()                              { t.erase(t.begin(), t.end());          }

	iterator begin()             { return t.begin(); }
	const_iterator begin() const { return t.begin(); }

	iterator end()               { return t.end(); }
	const_iterator end() const   { return t.end(); }

private:
	stree<pair<const Key,T> > t;
};

}
#endif	// MINIMAP_CLASS

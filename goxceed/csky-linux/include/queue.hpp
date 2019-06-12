#ifndef QUEUE_CLASS
#define QUEUE_CLASS

#include "list.hpp"
#include "except.hpp"

namespace gx {
template <typename T> class queue {
public:
	queue() {}

	void push(const T& item) { qlist.push_back(item);}
	void pop() {
		if (qlist.size() == 0)
			throw underflowError("queue pop(): empty queue");

		qlist.pop_front();
	}

	T& front() {
		if (qlist.size() == 0)
			throw underflowError("queue front(): empty queue");

		return qlist.front();
	}
	const T& front() const {
		if (qlist.size() == 0)
			throw underflowError("queue front(): empty queue");

		return qlist.front();
	}

	T& back() {
		if (qlist.size() == 0)
			throw underflowError("queue back(): empty queue");

		return qlist.back();
	}

	const T& back() const {
		if (qlist.size() == 0)
			throw underflowError("queue back(): empty queue");

		return qlist.back();
	}

	int size() const { return qlist.size(); }

	bool empty() const { return qlist.empty(); }
private:
	list<T> qlist;
};

}

#endif


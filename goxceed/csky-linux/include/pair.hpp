#ifndef MINIPAIR_CLASS
#define MINIPAIR_CLASS

namespace gx {

template<typename T1, typename T2> class pair {
public:
	T1 first;
	T2 second;

	pair(): first(T1()), second(T2()) {}

	pair(const T1& v1, const T2& v2): first(v1), second(v2) {}

	friend bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first < rhs.first;
	}

	friend bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first == rhs.first;
	}
};

}

#endif


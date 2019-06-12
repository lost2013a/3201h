#ifndef STRING_HPP
#define STRING_HPP

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ostream>
#include <istream>

#include "gxlib/gxlib.h"

namespace gx {

class string {
public:
	string()                    : _string(NULL), _count(0) { reserve(0);                             }
	string(const char *const s) : _string(NULL), _count(0) { allocate_and_copy(s, __strlen(s));        }
	string(const string& s)     : _string(NULL), _count(0) { allocate_and_copy(s._string, s._count); }
	string(size_t s, char c)    : _string(NULL), _count(0) { allocate_and_fill(c, s);                }

	~string() { gx_free(_string); }

	typedef char* iterator;

	iterator begin() { return _string; }
	iterator end()   { return _string + _count; }

	string operator + (const string& s)   { string tmp(_string); tmp += s; return tmp; }
	string operator + (const char *s)     { string tmp(_string); tmp += s; return tmp; }
	string operator + (const char c)      { string tmp(_string); tmp += c; return tmp; }

	string& operator= (const string& s)   { clear(); return append(s); }
	string& operator= (const char *s)     { clear(); return append(s); }
	string& operator= (const char c)      { clear(); return append(c); }

	string& operator+=(const string& s)   { return append(s); }
	string& operator+=(const char *s)     { return append(s); }
	string& operator+=(char c)            { return append(1, c); }

	char& operator[] (size_t index)       { return index > _count && index < 0 ? _string[_count - 1] : _string[index];}
	char  operator[] (size_t index) const { return index > _count && index < 0 ? _string[_count - 1] : _string[index];}


	void insert(size_t pos, char c)                  { insert_and_fill(pos, c, 1);                }
	void insert(size_t pos, string& s)               { insert_and_copy(pos, s._string, s._count); }
	void insert(size_t pos, const char *s)           { insert_and_copy(pos, s, __strlen(s));        }
	void insert(size_t pos, const char *s, size_t n) { insert_and_copy(pos, s, n);                }

	void push_back(char c) { allocate_and_fill(c, 1); }
	void clear()           { resize(0);               }
	void resize(size_t n)  { resize(n, 0);            }

	void resize(size_t n, char c) {
		if (reserve(n) == true) {
			if (n > _count)
				memset(_string + _count, c, n - _count);
			_count = n;
		}
	}

	string& erase(size_t pos, size_t len) {
		if (len + pos > _count)
			len = _count - pos;

		memmove(_string + pos, _string + pos + len, _count - len);
		_count -= len;
		reserve(_count);

		return *this;
	}

	string& assign(const string& s)                         { resize(0); return append(s);                  }
	string& assign(const char *s)                           { resize(0); return append(s);                  }
	string& assign(const char *s, size_t n)                 { resize(0); return append(s, n);               }
	string& assign(const char *s, const char *e)            { resize(0); return append(s, e - s);           }
	string& assign(size_t n, char c)                        { resize(0); return append(c, n);               }
	string& assign(const string& s, size_t pos, size_t len) { resize(0); return append(_string + pos, len); }

	string& append(const string& s)         { allocate_and_copy(s._string, s._count); return *this; }
	string& append(const char *s)           { allocate_and_copy(s, __strlen(s));      return *this; }
	string& append(const char *s, size_t n) { allocate_and_copy(s, n);                return *this; }
	string& append(size_t n, char c)        { allocate_and_fill(c, n);                return *this; }
	string& append(char c)                  { allocate_and_fill(c, 1);                return *this; }

	int compare(const string& s) const      { return strcmp(_string, s._string); }
	int compare(const char *s) const        { return strcmp(_string, s);         }

	size_t size() const                     { return _count;      }
	size_t length() const                   { return _count;      }
	const char *c_str() const               { return _string;     }
	bool empty() const                      { return _count == 0; }
private:
	char *_string;
	size_t _count;

	size_t __strlen(const char *s) {
		return s ?  strlen(s) : 0;
	}

	void allocate_and_copy(const char *s, size_t n) {
		if (s && n) {
			if (reserve(_count + n) == true) {
				memcpy(_string + _count, s, n);
				_count += n;
			}
		}
	}

	void allocate_and_fill(char c, size_t n) {
		if (n > 0) {
			if (reserve(_count + n) == true) {
				memset(_string + _count, c, n);
				_count += n;
			}
		}
	}

	void insert_and_copy(size_t pos, const char *s, size_t n) {
		if (s && n) {
			if (reserve(_count + n) == true) {
				memmove(_string + pos + n, _string + pos, _count + n - pos);
				memcpy(_string + pos, s, n);
				_count += n;
			}
		}
	}

	void insert_and_fill(size_t pos, char c, size_t n) {
		if (n > 0) {
			if (reserve(_count + n) == true) {
				memmove(_string + pos + n, _string + pos, _count + n - pos);
				memset(_string + pos, c, n);
				_count += n;
			}
		}
	}

	bool reserve(size_t n) {
		char *tmp = (char*)gx_realloc(_string, n + 1);
		if (tmp) {
			_string = tmp;
			_string[n] = '\0';
			return true;
		}

		return false;
	}
};

#if 1
inline std::ostream& operator<< (std::ostream& os, const string& str) {

	os.write(str.c_str(), str.size());

	return os;
}

inline std::istream& operator>> (std::istream& is, string& str) {

	return is;
}

#endif

inline string operator+(const string& lhs, const string& rhs) {
	string s(lhs); s.append(rhs); return s;
}

inline string operator+(const char *lhs, const string& rhs) {
	string s(lhs); s.append(rhs); return s;
}

inline string operator+(const string& lhs, const char *rhs) {
	string s(lhs); s.append(rhs); return s;
}

inline bool operator!=(const string& lhs, const string& rhs) {
	return lhs.compare(rhs) != 0;
}

inline bool operator!=(const char *lhs, const string& rhs) {
	return rhs.compare(lhs) != 0;
}

inline bool operator!=(const string& lhs, const char *rhs) {
	return lhs.compare(rhs) != 0;
}

inline bool operator==(const string& lhs, const string& rhs) {
	return lhs.compare(rhs) == 0;
}

inline bool operator==(const char *lhs, const string& rhs) {
	return rhs.compare(lhs) == 0;
}

inline bool operator==(const string& lhs, const char *rhs) {
	return lhs.compare(rhs) == 0;
}

inline bool operator<(const string& lhs, const string& rhs) {
	return lhs.compare(rhs) < 0;
}

inline bool operator<(const char *lhs, const string& rhs) {
	return rhs.compare(lhs) < 0;
}

inline bool operator<(const string& lhs, const char *rhs) {
	return lhs.compare(rhs) < 0;
}

inline bool operator>(const string& lhs, const string& rhs) {
	return lhs.compare(rhs) > 0;
}

inline bool operator>(const char *lhs, const string& rhs) {
	return rhs.compare(lhs) > 0;
}

inline bool operator>(const string& lhs, const char *rhs) {
	return lhs.compare(rhs) > 0;
}

};

#endif


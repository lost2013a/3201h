#ifndef EXCEPTION_CLASSES
#define EXCEPTION_CLASSES

#include "string.hpp"

class baseException {
public:
	baseException(const gx::string& str = ""): msgString(str) {
		if (msgString == "")
			msgString = "Unspecified exception";
	}

	gx::string what() const {
		return msgString;
	}
protected:
	gx::string msgString;
};

// failure to allocate memory (new() returns NULL)
class memoryAllocationError: public baseException {
public:
	memoryAllocationError(const gx::string& msg = ""): baseException(msg) {}
};

// function argument out of proper range
class rangeError: public baseException {
public:
	rangeError(const gx::string& msg = ""): baseException(msg) {}
};

// index out of range
class indexRangeError: public baseException {
public:
	indexRangeError(const gx::string& msg, int i, int size): baseException() {
#if 0
		ostringstream indexErr;

		indexErr << msg << "  index " << i << "  size = " << size << ends;
		msgStrin sionError= indexErr.str();
#endif
	}
};

// attempt to erase from an empty container
class underflowError: public baseException {
public:
	underflowError(const gx::string& msg = ""): baseException(msg) {}
};

// attempt to insert into a full container
class overflowError: public baseException {
public:
	overflowError(const gx::string& msg = ""): baseException(msg) {}
};

// bad object reference
class referenceError: public baseException {
public:
	referenceError(const gx::string& msg = ""): baseException(msg) {}
};

#endif	// EXCEPTION_CLASSES

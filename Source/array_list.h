#pragma once
#include <algorithm>
#include <string>
#include <sstream>

/** Represents an array-list, also known as a vector.*/
template <typename T>
class array_list {
public:
	/** The default initial size of an array-list. */
	static const size_t DEFAULT_SIZE = 16;
	explicit array_list(size_t size) {
		len = size;
		backing = new T[size];
	}
	array_list() : array_list(DEFAULT_SIZE) {}
	void add(T t) {
		if (pos >= len)
			expand();
		backing[pos++] = t;
	}
	/** Converts this array-list into a readable format. */
	std::string to_string() {
		std::ostringstream str;
		str << '[';
		for (size_t index = 0; index < pos; index++) {
			if (index != 0) str << ", ";
			str << backing[index];
		}
		str << ']';
		return str.str();
	}
	size_t size() const {
		return len;
	}
	~array_list() {
		delete[] backing;
	}
private:
	size_t len;
	size_t pos = 0;
	T* backing;
	void expand() {
		size_t newLen = std::max(len + len, 1u);
		T* newArray = new T[newLen];
		memcpy(newArray, backing, sizeof(T) * len);
		delete[] backing;
		backing = newArray;
		len = newLen;
	}
};
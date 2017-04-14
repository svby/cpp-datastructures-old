#pragma once
#include <algorithm>
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
	T* last() {
		return empty() ? nullptr : &backing[max_accessed];
	}
	T* first() {
		return empty() ? nullptr : &backing[0];
	}
	void remove() {
		pos--;
	}
	bool contains(T element) {
		for (size_t index = 0; index < size(); index++)
			if (backing[index] == element) return true;
		return false;
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
	bool empty() const {
		return pos == 0;
	}
	size_t size() const {
		return pos;
	}
	~array_list() {
		delete[] backing;
	}
	T& operator[](size_t index) {
		if (index >= len) throw std::out_of_range("out of range index");
		max_accessed = std::max(max_accessed, index);
		return backing[index];
	}
	void expand(size_t len) {
		T* newArray = new T[len];
		memcpy(newArray, backing, sizeof(T) * std::min(len, this->len));
		delete[] backing;
		backing = newArray;
		this->len = len;
	}
private:
	size_t len;
	size_t pos = 0;
	size_t max_accessed = pos;
	T* backing;
	void expand() {
		expand(std::max(len + len, 1u));
		size_t newLen = std::max(len + len, 1u);
		T* newArray = new T[newLen];
		memcpy(newArray, backing, sizeof(T) * len);
		delete[] backing;
		backing = newArray;
		len = newLen;
	}
};
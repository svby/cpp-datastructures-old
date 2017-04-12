#pragma once
#include <array>
#include <sstream>

/**
 * Represents a Fenwick tree/binary indexed tree.
 */
template <typename T>
class fenwick_tree {
public:
	/** Creates a new Fenwick tree from the specified pointer and size. */
	fenwick_tree(T* arr, size_t n) {
		len = n;
		init(arr);
	}
	/** Creates a new Fenwick tree from the specified array. */
	template <size_t N>
	fenwick_tree(const T(&arr)[N]) {
		len = N;
		init(arr);
	}
	/** Deletes the backing array of this Fenwick tree. */
	~fenwick_tree() {
		delete[] backing;
	}
	/** Returns the size of this Fenwick tree. */
	size_t size() const {
		return len;
	}
	/** Converts this Fenwick tree into a readable format. */
	std::string to_string() {
		std::ostringstream str;
		str << '[';
		for(size_t index = 0; index < len; index++) {
			if (index != 0) str << ", ";
			str << backing[index];
		}
		str << ']';
		return str.str();
	}
	/**
	 * Performs a query in the range [0, to).
	 */
	T query(size_t to) {
		T sum = 0;
		while(to > 0) {
			sum += backing[to];
			to -= to & ~to + 1;
		}
		return sum;
	}
	/**
	 * Performs a range query in the range [from, to).
	 * This is equivalent to query(to) - query(from).
	 */
	T query(size_t from, size_t to) {
		return query(to) - query(from);
	}
	/** Updates the value at the specified index. */
	void update(size_t index, T value) {
		index++;
		while (index <= len) {
			backing[index] += value;
			index += index & ~index + 1;
		}
	}
private:
	T* backing;
	size_t len;
	void init(const T* array) {
		backing = new T[len + 1];
		memset(backing, 0, len * sizeof(T));
		for (size_t i = 0; i < len; i++)
			update(i, array[i]);
	}
};

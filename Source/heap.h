#pragma once
#include <algorithm>

/**
* Represents a min-binary-heap, internally represented as an array.
* Also known as a priority queue.
*/
template <typename T, class Comparator = std::less<T>>
class heap {
public:
	/** The default initial size of a heap. */
	static const size_t DEFAULT_SIZE = 16;
	/** Verifies whether or not an array is a valid heap. */
	template <size_t N>
	static bool is_heap(T(&arr)[N]) {
		return is_heap(arr, N);
	}
	/** Verifies whether or not a pointer is a valid heap. */
	static bool is_heap(T* array, size_t size) {
		return is_heap(array, size, 0);
	}
	/**
	 * Returns the parent of this heap node.
	 * Calculates <pre>child - 1 >> 1</pre>.
	 */
	static size_t parent(size_t child) {
		return child - 1 >> 1;
	}
	/**
	* Returns the left child of this heap node.
	* Calculates <pre>(parent << 1) + 1</pre>.
	*/
	static size_t left(size_t parent) {
		return (parent << 1) + 1;
	}
	/**
	* Returns the left child of this heap node.
	* Calculates <pre>(parent << 1) + 2</pre>.
	*/
	static size_t right(size_t parent) {
		return (parent << 1) + 2;
	}
	/** Performs the heapify-down operation on an array at a specified repair site. */
	template<size_t N>
	static void heapifyDown(T(&arr)[N], size_t repair) {
		heapifyDown(arr, N, repair);
	}
	/** Performs the heapify-down operation on a pointer at a specified repair site. */
	static void heapifyDown(T* array, size_t size, size_t repair) {
		Comparator comp = Comparator();
		size_t smallest = repair;
		size_t lChild = left(repair), rChild = right(repair);
		if (lChild < size && comp(array[lChild], array[smallest]))
			smallest = lChild;
		if (rChild < size && comp(array[rChild], array[smallest]))
			smallest = rChild;
		if (smallest == repair) return;
		std::swap(array[smallest], array[repair]);
		heapifyDown(array, size, smallest);
	}
	/** Performs the heapify-up operation on an array at a specified repair site. */
	template<size_t N>
	static void heapifyUp(const T(&arr)[N], size_t repair) {
		heapifyUp(arr, repair);
	}
	/** Performs the heapify-up operation on a pointer at a specified repair site. */
	static void heapifyUp(T* array, size_t repair) {
		Comparator comp = Comparator();
		if (repair == 0) return;
		size_t parentIndex = parent(repair);
		if (comp(array[repair], array[parentIndex])) {
			std::swap(array[repair], array[parentIndex]);
			heapifyUp(array, parentIndex);
		}
	}
	/** Creates a new binary heap with the specified initial capacity. */
	heap(size_t size) {
		len = size;
		backing = new T[size];
	}
	/** Creates a binary heap of size <pre>DEFAULT_SIZE</pre>. */
	heap() : heap(DEFAULT_SIZE) {}
	void push(T t) {
		backing[pos] = t;
		heapifyUp(backing, pos);
		pos++;
		if (pos >= len)
			expand();
	}
	/** Helper method to push all values in an array. */
	template<size_t N>
	void push_all(const T(&arr)[N]) {
		push_all(arr, N);
	}
	/** Helper method to push all values in an array. */
	void push_all(T* array, size_t size) {
		for (size_t index = 0; index < size; index++)
			push(array[index]);
	}
	/** Returns a pointer to the top element of this heap, or <pre>nullptr</pre> if it is empty. */
	T* top() {
		return empty() ? nullptr : &backing[0];
	}
	/**
	 * Removes the top element of this heap and restructures it.
	 * Throws <pre>out_of_range</pre> if the heap is empty.
	 */
	void pop() {
		if (empty()) throw std::out_of_range("heap is empty");
		std::swap(backing[pos - 1], backing[0]);
		pos--;
		heapifyDown(backing, pos, 0);
	}
	/** Clears the backing array of this heap. */
	void clear() {
		memset(backing, 0, sizeof(T) * pos);
		pos = 0;
	}
	/** Returns the size of this heap. */
	size_t size() const {
		return pos;
	}
	/** Returns whether or not this heap is empty (i.e. <pre>size() == 0</pre>). */
	bool empty() const {
		return pos == 0;
	}
	/** Converts this heap into a readable format. */
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
	/** Deletes the backing array of this heap. */
	~heap() {
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
	static bool is_heap(T* array, size_t size, size_t point) {
		size_t parent = array[point];
		size_t lChild = left(parent), rChild = right(parent);
		Comparator comp = Comparator();
		bool works = true;
		if (lChild < size) {
			if (comp(array[lChild], parent)) return false;
			works &= is_heap(array, size, lChild);
		} if (rChild < size && works) {
			if (comp(array[rChild], parent)) return false;
			return true;
		} return true;
	}
};
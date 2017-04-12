#include <iostream>
#include <string>
#include "fenwick.h"
#include "union_find.h"
#include "heap.h"
#include <queue>
#include <ctime>

using std::cout;
using std::string;

template <typename T, size_t N>
std::ostream& print_array(const T(&arr)[N]) {
	cout << '[';
	for (size_t index = 0; index < N; ++index) {
		if (index != 0)
			cout << ", ";
		cout << arr[index];
	} cout << "]\n";
	return cout;
}

void fenwick() {
	int is[10]{ 1, 5, 3, 4, 7, -3, 0, -4, 1, 3 };
	fenwick_tree<int> ft(is);
	cout << ft.query(5, 8) << '\n';
}

void unionFind() {
	union_find<int> uf(5);
	cout << uf.find(3) << '\n';
	cout << uf.sets() << '\n';
	uf.merge(1, 3);
	cout << uf.sets() << '\n';
	uf.merge(2, 1);
	cout << uf.find(2) << '\n';
	cout << uf.connected(2, 4) << '\n';
	uf.merge(2, 4);
	cout << uf.connected(2, 4) << '\n';
}

void binaryHeap() {
	string strings[8]{ "Hello", "hello", "hEllo", "HellO", "HELLO", "ehLo", "asd", "HeLLo"};
	heap<string> bh;
	bh.push_all(strings, 8);
	cout << bh.to_string() << '\n';
	bh.clear();
	cout << bh.to_string() << '\n';
}

int main() {
	binaryHeap();
	getchar();
}

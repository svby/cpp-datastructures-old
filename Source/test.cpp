#include <iostream>
#include <string>
#include "fenwick_tree.h"
#include "union_find.h"
#include "heap.h"
#include "interval_tree.h"
#include "trie.h"
#include "array_list.h"

using std::cout;
using std::string;

template <typename T, size_t N>
std::ostream& print_array(T(&arr)[N]) {
	cout << '[';
	for (size_t index = 0; index < N; ++index) {
		if (index != 0)
			cout << ", ";
		cout << arr[index];
	} cout << "]\n";
	return cout;
}

void test_fenwick_tree() {
	int is[10]{ 1, 5, 3, 4, 7, -3, 0, -4, 1, 3 };
	fenwick_tree<int> ft(is);
	cout << ft.query(5, 8) << '\n';
	cout << ft << '\n';
}

void test_union_find() {
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

void test_heap() {
	string strings[8]{ "Hello", "hello", "hEllo", "HellO", "HELLO", "ehLo", "asd", "HeLLo" };
	heap<string> bh;
	bh.push_all(strings);
	cout << bh.to_string() << '\n';
	bh.clear();
	cout << bh.to_string() << '\n';
}

void test_interval_tree() {
	interval_tree<int> tree;
	tree.insert(2, 4);
	tree.insert(3, 7);
	tree.insert(5, 8);
	tree.insert(1, 5);
	auto query = tree.query_all(3);
	for (auto interval : query) {
		cout << interval << '\n';
	}
	tree.root()->process_overlaps(3, [](auto ivl) {
		cout << ivl << '\n';
	});
}

void test_trie() {
	trie<int> t;
	t.add("Apple");
	t.add("Apple");
	t.add("Apple");
	t.add("Application");
	t.add("Applejack");
	t.add("App");
	t.add("Applause");
	t.add("Apple");
	cout << t.root()->get("Apple") << '\n';
	cout << t.root()->get("Application") << '\n';
	cout << t.root()->get("App") << '\n';
	cout << t.root()->get("A") << '\n';
}

void test_array_list() {
	array_list<int> list;
	list.expand(10);
	list[0] = 2;
	cout << list[0] << '\n';
}

int main() {
	test_trie();
	cout << "Done. Press enter to continue...\n";
	getchar();
}

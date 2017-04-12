#include <iostream>
#include <string>
#include "fenwick.h"
#include "union_find.h"

using namespace std;

void fenwick() {
	int is[10]{ 1, 5, 3, 4, 7, -3, 0, -4, 1, 3 };
	fenwick_tree<int> a(is);
	cout << a.query(5, 8) << '\n';
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

int main() {
	unionFind();
	getchar();
}

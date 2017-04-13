#pragma once
#include <cstring>

template<typename T>
class union_find {
public:
	explicit union_find(T nodes) {
		count = nodes;
		parents = new T[nodes];
		ranks = new T[nodes];
		for (T i = 0; i < nodes; ++i) {
			parents[i] = i;
			ranks[i] = 1;
		}
		rankCount = nodes;
	}
	~union_find() {
		delete[] parents;
		delete[] ranks;
	}
	T find(T i) {
		T root = i;
		while (root != parents[root]) root = parents[root];
		while (i != root) {
			T newI = parents[i];
			parents[i] = root;
			i = newI;
		} return root;
	}
	void merge(T a, T b) {
		T rootA = find(a), rootB = find(b);
		if (rootA == rootB)
			return;
		if(ranks[rootA] < ranks[rootB]) {
			parents[rootA] = rootB;
			ranks[rootB] += ranks[rootA];
		} else {
			parents[rootB] = rootA;
			ranks[rootA] += ranks[rootB];
		}
		--rankCount;
	}
	bool connected(T a, T b) {
		return find(a) == find(b);
	}
	T sets() {
		return rankCount;
	}
	T size() {
		return count;
	}
private:
	T count, rankCount, *parents, *ranks;
};

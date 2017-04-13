#pragma once
#include <functional>
#include <vector>

template<typename T>
class interval_tree {
	static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");
public:
	struct interval {
		friend interval_tree;
		bool overlaps(interval& other) {
			return lo <= other.hi && other.lo <= hi;
		}
		std::string to_string() {
			std::ostringstream str;
			str << '[' << lo << " -> " << hi << ']';
			return str.str();
		}
		friend std::ostream& operator << (std::ostream& ostream, interval& interval) {
			ostream << interval.to_string();
			return ostream;
		}
		interval(T low, T high) : lo(low), hi(high) {}
		interval() : interval(0, 0) {}
		T low() {
			return lo;
		}
		T high() {
			return hi;
		}
	private:
		T lo, hi;
	};
	struct node {
		friend interval_tree;
		void traverse(std::function<void(interval)> func) {
			if (lnode != nullptr) lnode->traverse(func);
			func(i);
			if (rnode != nullptr) rnode->traverse(func);
		}
		interval interval() {
			return i;
		}
		T max() {
			return max_value;
		}
		node* left() {
			return lnode;
		}
		node* right() {
			return rnode;
		}
	private:
		explicit node(typename interval_tree<T>::interval interval) {
			i = interval;
			max_value = interval.hi;
			lnode = rnode = nullptr;
		}
		typename interval_tree<T>::interval i;
		T max_value;
		node* lnode, *rnode;
	};
	interval_tree() {
		root_node = nullptr;
	}
	node* root() {
		return root_node;
	}
	node* insert(interval ivl) {
		auto res = insert(root_node, ivl);
		root_node = std::get<0>(res);
		return std::get<1>(res);
	}
	node* insert(T low, T high) {
		return insert(low, high);
	}
	void traverse(std::function<void(interval)> function) {
		if (root_node != nullptr)
			root_node->traverse(function);
	}
	void process_overlaps(node* root, interval i, std::function<void(interval)> function) {
		if (root == nullptr) return;
		if (i.overlaps(root->i))
			function(root->i);
		if (root->lnode != nullptr && root->lnode->max_value >= i.lo)
			process_overlaps(root->lnode, i, function);
		process_overlaps(root->rnode, i, function);
	}
	void process_overlaps(node* root, T value, std::function<void(interval)> function) {
		process_overlaps(root, { value, value }, function);
	}
	void process_overlaps(interval i, std::function<void(interval)> function) {
		process_overlaps(root_node, i, function);
	}
	void process_overlaps(T value, std::function<void(interval)> function) {
		process_overlaps(root_node, { value, value }, function);
	}
	std::vector<interval> query_all(node* root, interval i) {
		std::vector<interval> vector;
		overlaps(root, &vector, i);
		return vector;
	}
	std::vector<interval> query_all(node* root, T point) {
		return query_all(root, { point, point });
	}
	std::vector<interval> query_all(interval i) {
		std::vector<interval> vector;
		overlaps(root_node, &vector, i);
		return vector;
	}
	std::vector<interval> query_all(T point) {
		return query_all(root_node, { point, point });
	}
private:
	node* root_node;
	void overlaps(node* root, std::vector<interval>* list, interval i) {
		if (root == nullptr) return;
		if (i.overlaps(root->i))
			list->emplace_back(root->i);
		if (root->lnode != nullptr && root->lnode->max_value >= i.lo)
			overlaps(root->lnode, list, i);
		overlaps(root->rnode, list, i);
	}
	std::pair<node*, node*> insert(node* root, interval ivl) {
		if (root == nullptr) {
			node* newNode = new node(ivl);
			return std::pair<node*, node*>(newNode, newNode);
		}
		root->max_value = std::max(root->max_value, ivl.hi);
		if (root->max_value < ivl.hi)
			root->max_value = ivl.hi;
		if (ivl.lo < root->i.lo)
			return std::pair<node*, node*>(root, root->lnode = std::get<0>(insert(root->lnode, ivl)));
		return std::pair<node*, node*>(root, root->rnode = std::get<0>(insert(root->rnode, ivl)));
	}
};

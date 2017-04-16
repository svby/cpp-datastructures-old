#pragma once
#include <string>
#include <map>
#include <unordered_map>

#define TRIE_IMPL 2

template<typename T>
class trie {
	static_assert(std::is_arithmetic<T>::value, "Type must be arithmetic");
public:
	struct node {
		friend trie;
		bool isEnd() const {
			return end_here != 0;
		}
		T end() const {
			return end_here;
		}
		char value() const {
			return val;
		}
		node* add_children(const char* values, size_t len) {
			if (len == 0) {
				++end_here;
				return this;
			}
			auto iter = nodes.find(*values);
			node* modify;
			if (iter == nodes.end()) {
				nodes[*values] = modify = new node(*values, len == 1 ? 1 : 0);
				if (len == 1) return modify;
			}
			else modify = iter->second;
			if (len >= 1) modify->add_children(values + 1, len - 1);
			return modify;
		}
		T get(const char* values, size_t len) {
			if (len == 0) return end_here;
			auto iter = nodes.find(*values);
			return iter == nodes.end() ? 0 : iter->second->get(values + 1, len - 1);
		}
		T get(std::string str) {
			return get(str.c_str(), str.length());
		}
		bool contains(const char* str, size_t len) {
			return get(str, len) != 0;
		}
		bool contains(std::string str) {
			return contains(str.c_str(), str.length());
		}
		explicit node(char val, T end) : end_here(end), val(val) {}
	private:
		T end_here = 0;
		char val;
		std::unordered_map<char, node*> nodes;
	};
	void add(const char* str, size_t len) const {
		root_node->add_children(str, len);
	}
	void add(std::string str) const {
		add(str.c_str(), str.length());
	}
	explicit trie() {
		root_node = new node('\0', false);
	}
	node* root() const {
		return root_node;
	}
	~trie() {
		delete root_node;
	}
private:
	node* root_node;
};

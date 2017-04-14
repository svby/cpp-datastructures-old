#pragma once
#include <string>
#include <map>
#include <unordered_map>

class trie {
public:
	struct node {
		friend trie;
		bool end() const {
			return END;
		}
		char value() const {
			return val;
		}
		node* add_children(const char* values, size_t len);
		node* get_child(char value);
		void traverse();
		bool contains(const char* str, size_t len);
		bool contains(std::string str) {
			return contains(str.c_str(), str.length());
		}
		template<size_t len>
		bool contains(const char(&str)[len]) const {
			return contains(str, len);
		}
		explicit node(char val, bool end) : END(end), val(val) {}
	private:
		bool END;
		char val;
		std::unordered_map<char, node*> nodes;
		void traverse(std::vector<char>* prog);
	};
	void add(const char* str, size_t len) const;
	void add(std::string str) const {
		add(str.c_str(), str.length());
	}
	template<size_t len>
	void add(const char(&str)[len]) {
		add(str, len);
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

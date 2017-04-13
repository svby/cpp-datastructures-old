#include "trie.h"
#include <iostream>

void trie::add(const char* str, size_t len) const {
	root_node->add_children(str, len);
}

trie::node* trie::node::get_child(char value) {
	auto iterator = nodes.find(value);
	return iterator == nodes.end() ? nullptr : iterator->second;
}

trie::node* trie::node::add_children(const char* values, size_t len) {
	if (len == 0) {
		END = true;
		return this;
	}
	auto iter = nodes.find(*values);
	node* modify = nullptr;
	if(iter == nodes.end())
		nodes[*values] = modify = new node(*values, len == 1);
	else modify = iter->second;
	if (len > 1)
		modify->add_children(values + 1, len - 1);
	return modify;
}

bool trie::node::contains(const char* str, size_t len) {
	if (len == 0) return END;
	auto iterator = nodes.find(*str);
	return iterator != nodes.end() && iterator->second->contains(str + 1, len - 1);
}

bool trie::contains(const char* str, size_t len) const {
	return root_node->contains(str, len);
}

void trie::node::traverse(std::vector<char>* prog) {
	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		prog->push_back(it->first);
		if (it->second->END) std::cout << std::string(prog->begin(), prog->end()) << '\n';
		it->second->traverse(prog);
		prog->pop_back();
	}
}

void trie::node::traverse() {
	auto vec = new std::vector<char>();
	traverse(vec);
	delete vec;
}

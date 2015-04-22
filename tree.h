
#ifndef BF_TREE_H_
#define BF_TREE_H_

#include "tok.h"

#include <vector>

namespace bf {

class tree {
public:
	tree() {}
	~tree() {
		delete root;
	}
	void put(tok item) {
		if (root == nullptr) {
			root = new node<tok>(item);
		} else {
			auto nd = root;
			while (nd->item().token()->first == tok::BEGIN_LOOP) {
				if (nd->child_nodes.size() > 0) {
					nd = &*nd->child_nodes.end(); // descend
				} else {
					break;
				}
			}
			nd->child_nodes.push_back(node<tok>(item));
		}
	}
private:
	template <typename t>
	class node {
	public:
		std::vector<node<t>> child_nodes;

		node(t item) : item_(item) {}
		~node() {}
		t item() const {
			return item_;
		}
	private:
		t item_;
	};

	node<tok> *root = nullptr;
};

} // namespace bf

#endif // BF_TREE_H_

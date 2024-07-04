#ifndef API_BEHAVIOUR_TREE_TREE_H_
#define API_BEHAVIOUR_TREE_TREE_H_
#include <memory>

#include "node.h"

namespace behaviour_tree
{
	class Tree 
	{
	private:
		Node* root_;
	public:
		~Tree();
		void Tick();
		void AttachNode(Node* node);
	};
}

#endif //API_BEHAVIOUR_TREE_TREE_H_

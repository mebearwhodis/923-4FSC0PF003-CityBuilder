#ifndef API_BEHAVIOUR_TREE_TREE_H_
#define API_BEHAVIOUR_TREE_TREE_H_
#include <memory>

#include "leaf.h"
#include "node.h"
#include "selector.h"
#include "sequence.h"

using namespace behaviour_tree;

	class Tree 
	{
	private:
		std::unique_ptr<Node> root_ = nullptr;
	public:
		void Tick() const;
		void Attach(std::unique_ptr<Leaf>& node);
		void Attach(std::unique_ptr<Sequence>& node);
		void Attach(std::unique_ptr<Selector>& node);
	};


#endif //API_BEHAVIOUR_TREE_TREE_H_

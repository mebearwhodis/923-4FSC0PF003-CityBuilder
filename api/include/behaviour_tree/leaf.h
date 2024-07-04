#ifndef API_BEHAVIOUR_TREE_LEAF_H_
#define API_BEHAVIOUR_TREE_LEAF_H_
#include <functional>

#include "node.h"


namespace behaviour_tree
{
	class Leaf : public Node
	{

	private:
		std::function<Status()> leaf_action_;

	public:
		Status Process() override;

		Leaf(const std::function<Status()>& leaf_action) : leaf_action_(leaf_action) { };
	};
}

#endif //API_BEHAVIOUR_TREE_LEAF_H_
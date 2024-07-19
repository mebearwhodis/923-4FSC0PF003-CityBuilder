#ifndef API_BEHAVIOUR_TREE_LEAF_H_
#define API_BEHAVIOUR_TREE_LEAF_H_
#include <functional>

#include "node.h"

using namespace behaviour_tree;

	class Leaf final : public Node
	{
	private:
		std::function<Status()> leaf_action_;

	public:
		Leaf(const std::function<Status()>& leaf_action) : leaf_action_(leaf_action) { }
		Status Process() override;
		void Reset() override {}
	};
#endif //API_BEHAVIOUR_TREE_LEAF_H_
#ifndef API_BEHAVIOUR_TREE_NODE_H_
#define API_BEHAVIOUR_TREE_NODE_H_
#include <vector>

namespace behaviour_tree
{
	enum class Status
	{
		kRunning,
		kFailure,
		kSuccess
	};

	class Node
	{
	private:
		std::vector<Node> children_;

	public:
		~Node() = default;
		virtual Status Process();

		void AddNode(const Node& node);
	};
}

#endif //API_BEHAVIOUR_TREE_NODE_H_
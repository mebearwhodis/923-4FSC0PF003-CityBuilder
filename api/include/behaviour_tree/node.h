#ifndef API_BEHAVIOUR_TREE_NODE_H_
#define API_BEHAVIOUR_TREE_NODE_H_
#include <memory>
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
	public:
		virtual ~Node() = default;
		virtual Status Process() = 0;
	};



	class NodeList : public Node
	{
	protected:
		int current_child_ = 0;
		std::vector<Node*> children_;

	public:
		void AddNode(Node* node);
	};

	inline void NodeList::AddNode(Node* node)
	{
		children_.push_back(node);
	}
}

#endif //API_BEHAVIOUR_TREE_NODE_H_
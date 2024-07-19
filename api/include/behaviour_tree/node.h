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
	public:
		virtual ~Node() = default;
		virtual Status Process() = 0;
		virtual void Reset() = 0;
	};

	class NodeList : public Node
	{
	protected:
		int current_child_ = 0;
		std::vector<Node*> children_;

	public:
		void AddNode(Node* node);
		void Reset() override;
	};

	inline void NodeList::AddNode(Node* node)
	{
		children_.push_back(node);
	}

	inline void NodeList::Reset()
	{
		current_child_ = 0;
	}
}
#endif //API_BEHAVIOUR_TREE_NODE_H_
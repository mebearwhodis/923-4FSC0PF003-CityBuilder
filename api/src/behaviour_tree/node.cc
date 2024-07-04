#include "behaviour_tree/node.h"

using namespace behaviour_tree;

Status Node::Process()
{
	return Status::kFailure;
}

void Node::AddNode(const Node& node)
{
	//Control if valid
	children_.emplace_back(node);
}

#include "behaviour_tree/leaf.h"

using namespace behaviour_tree;

Status Leaf::Process()
{
	if(leaf_action_ != nullptr)
	{
		return leaf_action_();
	}else
	{
		return Status::kFailure;
	}
}

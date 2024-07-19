#include "behaviour_tree/selector.h"

Status Selector::Process()
{
	if (current_child_ < children_.size())
	{
		const Status status = children_[current_child_]->Process();
		if (status == Status::kFailure)
		{
			children_[current_child_]->Reset();
			current_child_++;
			if (current_child_ >= children_.size())
			{
				current_child_ = 0;
				return Status::kFailure;
			}
			else
			{
				return Status::kRunning;
			}
		}

		return status;
	}

	return Status::kFailure;
}
#include "behaviour_tree/sequence.h"

Sequence::~Sequence() = default;

Status Sequence::Process()
{
	if (current_child_ < children_.size())
	{
		const Status status = children_[current_child_]->Process();
		if (status == Status::kSuccess)
		{
			children_[current_child_]->Reset();
			current_child_++;
			if (current_child_ >= children_.size())
			{
				current_child_ = 0;
				return Status::kSuccess;
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
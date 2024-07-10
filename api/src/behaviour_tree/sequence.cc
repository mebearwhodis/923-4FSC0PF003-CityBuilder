#include "behaviour_tree/sequence.h"

Sequence::~Sequence() = default;

Status Sequence::Process()
{
	if(current_child_ < children_.size())
	{
		const Status status = children_[current_child_]->Process();
		if(status == Status::kSuccess)
		{
			current_child_++;
			if(current_child_ >= children_.size())
			{
				ResetSequence();
				return Status::kSuccess;
			}
			else
			{
				return Status::kRunning;
			}
		}
		else if(status == Status::kRunning)
		{
			return Status::kRunning;
		}
		else
		{
			ResetSequence();
			return status;
		}
	}
	
	return Status::kFailure;
}

void Sequence::ResetSequence()
{
	current_child_ = 0;
}

#include "behaviour_tree/tree.h"
#include <iostream>

using namespace behaviour_tree;

behaviour_tree::Tree::Tree()
{
	root_ = nullptr;
}

Tree::~Tree()
{
	delete root_;
}

void Tree::Tick()
{
	behaviour_tree::Status status;
	if(root_ != nullptr)
		status = root_->Process();

	switch (status) {
	case Status::kRunning:
		break;
	case Status::kFailure:
		break;
	case Status::kSuccess:
		break;
	default: 
		std::cout << "undefined state\n";
		break;
	}
}

void Tree::AttachNode(Node* node)
{
	root_ = node;
}

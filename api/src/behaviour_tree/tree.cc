#include "behaviour_tree/tree.h"
#include <iostream>

using namespace behaviour_tree;

Tree::Tree()
{
	root_ = nullptr;
}

Tree::~Tree()
{
	delete root_;
}

void Tree::Tick()
{
	if(root_ != nullptr)
	{
		Status status = root_->Process();
	}
}

void Tree::AttachNode(Node* node)
{
	root_ = node;
}

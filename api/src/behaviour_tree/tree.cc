//#include "behaviour_tree/tree.h"
//#include <iostream>
//
//using namespace behaviour_tree;
//
//Tree::~Tree()
//{
//	delete root_;
//}
//
//void Tree::Tick()
//{
//	behaviour_tree::Status status;
//	if(root_ != nullptr)
//		status = root_->Process();
//
//	switch (status) {
//	case Status::kRunning:
//		break;
//	case Status::kFailure:
//		break;
//	case Status::kSuccess:
//		break;
//	default: 
//		std::cout << "undefined state\n";
//		break;
//	}
//}
//
//void Tree::AttachNode(Node* node)
//{
//	root_ = node;
//}


#include "behaviour_tree/tree.h"
#include <iostream>

using namespace behaviour_tree;

Tree::Tree() : root_(nullptr) {}

Tree::~Tree() = default;

void Tree::Tick()
{
    if (!root_) {
        std::cout << "Tree root is null" << std::endl;
        return;
    }

    behaviour_tree::Status status = root_->Process();

    switch (status) {
    case Status::kRunning:
        break;
    case Status::kFailure:
        break;
    case Status::kSuccess:
        break;
    default:
        break;
    }
}

void Tree::AttachNode(std::unique_ptr<Node> node)
{
    root_ = std::move(node);
    std::cout << "Node attached to tree" << std::endl;
}

#ifndef API_BEHAVIOUR_TREE_SELECTOR_H_
#define API_BEHAVIOUR_TREE_SELECTOR_H_

#include "node.h"

using namespace behaviour_tree;

class Selector : public NodeList
{
public:
	Status Process() override;
	~Selector() override = default;
};
#endif // API_BEHAVIOUR_TREE_SELECTOR_H_

#ifndef API_BEHAVIOUR_TREE_SEQUENCE_H_
#define API_BEHAVIOUR_TREE_SEQUENCE_H_

#include "node.h"

using namespace behaviour_tree;

class Sequence : public NodeList
{
public:
	~Sequence() override;
	Status Process() override;
};
#endif // API_BEHAVIOUR_TREE_SEQUENCE_H_
#pragma once

#include "ASTNode.h"

class PrintNode : public ASTNode {

public:
	PrintNode(VAR_NODE_PTR var_node);
		/*
			Description: Constructs an PrintNode that contains a VAR_NODE that it prints.
		*/

	VAR_NODE_PTR getVariable();
		/*
			Description: Returns the VAR_NODE_PTR of the vairable node attached to this AssignNode
		*/

private:
	VAR_NODE_PTR var_node_;

};

#pragma once

#include "ASTNode.h"

class ReadNode : public ASTNode {

public:
	ReadNode(VAR_NODE_PTR var_node);
		/*
			Description: Constructs an PrintNode consisting of a VAR_NODE of the variable it prints. 
		*/

	VAR_NODE_PTR getVariable();
		/*
			Description: Returns a VAR_NODE_PTR of the variable it prints.
		*/

private:
	VAR_NODE_PTR var_node_;

};

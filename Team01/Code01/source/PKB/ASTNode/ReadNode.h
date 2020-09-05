#pragma once

#include "StatementNode.h"

class ReadNode : public StatementNode {

public:
	ReadNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Constructs an PrintNode consisting of a VAR_NODE of the variable it prints. 
		*/

	BOOLEAN setVariableNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Returns True if able to set var_node_ as var_node, false otherwise.
		*/

	VAR_NODE_PTR getVariableNode();
		/*
		Description: Returns a VAR_NODE_PTR of the variable it prints.
		*/

private:
	VAR_NODE_PTR var_node_ptr_;

};

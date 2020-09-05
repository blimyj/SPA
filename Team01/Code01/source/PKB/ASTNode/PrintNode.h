#pragma once

#include "StatementNode.h"

class PrintNode : public StatementNode {

public:
	PrintNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Constructs an PrintNode that contains a AST_NODE_PTR that it prints.
		*/

	BOOLEAN setVariableNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Returns True if able to set node_ as the var_node, false otherwise.
		*/

	VAR_NODE_PTR getVariableNode();
		/*
		Description: Returns the VAR_NODE_PTR of the variable node attached to this PrintNode.
		*/

private:
	VAR_NODE_PTR var_node_ptr_;

};

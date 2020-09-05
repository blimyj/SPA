#pragma once

#include "StatementNode.h"

class AssignNode : public StatementNode {

public:
	AssignNode(VAR_NODE_PTR var_node_ptr, EXPR_NODE_PTR expr_node_ptr);
		/*
		Description: Constructs an AssignNode based on the VAR_NODE and EXPR_NODE attached to it
		*/
		
	BOOLEAN setVariableNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Returns True if able to set var_node_ of this node to var_node_ptr, false otherwise.
		*/

	BOOEALN setExpressionNode(EXPR_NODE_PTR expr_node_ptr);
		/*
		Description: Returns True if able to set expr_node_ of this node to expr_node_ptr, false otherwise.
		*/

	VAR_NODE_PTR getVariableNode();
		/*
		Description: Returns the VAR_NODE_PTR of the variable node attached to this AssignNode
		*/

	EXPR_NODE_PTR getExpressionNode();
		/*
		Description: Returns the EXPR_NODE_PTR of the expression node attached to this AssignNode
		*/

private:
	VAR_NODE_PTR var_node_ptr_;
	EXPR_NODE_PTR expr_node_ptr_;

};

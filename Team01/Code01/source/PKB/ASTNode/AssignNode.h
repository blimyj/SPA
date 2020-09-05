#pragma once

#include "ASTNode.h"

class AssignNode : public ASTNode {

public:
	AssignNode(VAR_NODE_PTR var_node, EXPR_NODE_PTR expr_node);
		/*
			Description: Constructs an AssignNode based on the VAR_NODE and EXPR_NODE attached to it
		*/

	VAR_NODE_PTR getVariable();
		/*
			Description: Returns the VAR_NODE_PTR of the vairable node attached to this AssignNode
		*/

	EXPR_NODE_PTR getExpression();
		/*
			Description: Returns the EXPR_NODE_PTR of the expression node attached to this AssignNode
		*/

private:
	VAR_NODE_PTR var_node_;
	EXPR_NODE_PTR expr_node_;

};

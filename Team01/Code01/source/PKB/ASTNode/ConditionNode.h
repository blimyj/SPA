#pragma once

#include "ASTNode.h"

class ConditionNode : public ASTNode {

public:
	ConditionNode(RELATION_TYPE relation_type, AST_NODE_PTR left_node, AST_NODE_PTR right_node);
		/*
			Description: Constructs an ConditionNode consisting of a RELATION_TYPE, left and right AST_NODE_PTR.
		*/

	RELATION_TYPE getRelationType();
		/*
			Description: Returns the RELATION_TYPE of the condition.
		*/

	AST_NODE_PTR getLeftAstNode();
		/*
			Description: Returns the AST_NODE_PTR of the left hand side of the expression.
		*/


	AST_NODE_PTR getRightAstNode();
		/*
			Description: Returns the AST_NODE_PTR of the right hand side of the expression.
		*/


private:
	RELATION_TYPE relation_type_;
	AST_NODE_PTR left_node_;
	AST_NODE_PTR right_node_;

};

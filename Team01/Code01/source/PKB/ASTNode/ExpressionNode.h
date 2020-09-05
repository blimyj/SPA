#pragma once

#include "ASTNode.h"

class ExpressionNode : public ASTNode {

public:
	ExpressionNode(EXPR_TYPE expr_type, AST_NODE_PTR left_node, AST_NODE_PTR right_node);
		/*
			Description: Constructs an ExpressionNode consisting of a EXPR_TYPE, left and right AST_NODE_PTR.
		*/

	EXPR_TYPE getExpressionType();
		/*
			Description: Returns the EXPR_TYPE of this expression.
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
	EXPR_TYPE expr_type_;
	AST_NODE_PTR left_node_;
	AST_NODE_PTR right_node_;

};

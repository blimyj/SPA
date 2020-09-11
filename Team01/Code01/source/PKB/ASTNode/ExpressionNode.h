#pragma once

#include <memory>
#include <string>
#include "ASTNode.h"
#include "ExpressionTypeEnum.h"

typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef ExpressionTypeEnum EXPR_TYPE;
typedef bool BOOLEAN;

class ExpressionNode : public ASTNode {

public:
	ExpressionNode(EXPR_TYPE expr_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr);
		/*
		Description: Constructs an ExpressionNode consisting of a EXPR_TYPE, left and right AST_NODE_PTR.
		*/

	BOOLEAN setExpressionType(EXPR_TYPE expr_type);
		/*
		Description: Returns the EXPR_TYPE enum of the condition.
		Can be EXPR_TYPE enum of PLUS, MINUS, DIVIDE, MULTIPLY, MOD
		*/

	BOOLEAN setLeftAstNode(AST_NODE_PTR left_node_ptr);
		/*
		Description: Returns True if able to set left_node_ as left_node_ptr, false otherwise.
		left_node_ptr must be ExpressionNode, VariableNode or ConstantNode.
		*/


	BOOLEAN setRightAstNode(AST_NODE_PTR right_node_ptr);
		/*
		Description: Returns True if able to set right_node_ as right_node_ptr, false otherwise.
		right_node_ptr must be ExpressionNode, VariableNode or ConstantNode.
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
	AST_NODE_PTR left_node_ptr_;
	AST_NODE_PTR right_node_ptr_;

};

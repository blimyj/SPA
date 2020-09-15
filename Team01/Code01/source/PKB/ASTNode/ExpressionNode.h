#pragma once

#include <memory>
#include <string>
#include "ASTNode.h"
#include "ExpressionTypeEnum.h"

typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef ExpressionTypeEnum EXPR_TYPE;
typedef bool BOOLEAN;

class ExpressionNode : public ASTNode, std::enable_shared_from_this<ExpressionNode> {
/*ExpressionNode is +, -, *, / or none*/

public:
	ExpressionNode();
		/*
		Description: Sets NODE_TYPE of node to be expressionNode.
		*/

	BOOLEAN setExpressionType(EXPR_TYPE expr_type);
		/*
		Description: Returns True if able to set the EXPR_TYPE of this ExpressionNode, false otherwise.
		*/

	BOOLEAN setLeftAstNode(AST_NODE_PTR left_node_ptr);
		/*
		Description: Returns True if able to set AST_NODE_PTR to be the left-hand side 
		child of this Expression, false otherwise
		*/


	BOOLEAN setRightAstNode(AST_NODE_PTR right_node_ptr);
		/*
		Description: Returns True if able to set AST_NODE_PTR to be the right-hand side 
		child of this Condition, false otherwise.
		*/

	EXPR_TYPE getExpressionType();
		/*
		Description: Returns the EXPR_TYPE of this expression.
		*/

	AST_NODE_PTR getLeftAstNode();
		/*
		Description: Returns the left-hand side child AST_NODE_PTR of this Expression.
		*/


	AST_NODE_PTR getRightAstNode();
		/*
		Description: Returns the right-hand side child AST_NODE_PTR of this Expression.
		*/

private:
	EXPR_TYPE expr_type_;
	AST_NODE_PTR left_node_ptr_;
	AST_NODE_PTR right_node_ptr_;

};

#pragma once

#include <memory>
#include <string>
#include "ASTNode.h"
#include "VariableNode.h"

typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef std::string CONDITION_TYPE;
typedef bool BOOLEAN;

class ConditionNode : public StatementNode {

public:
	ConditionNode(CONDITION_TYPE condition_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr);
		/*
		Description: Constructs an ConditionNode consisting of a CONDITION_TYPE, left and right AST_NODE_PTR.
		*/

	BOOLEAN setRelationType(CONDITION_TYPE condition_type);
		/*
		Description: Returns the CONDITION_TYPE enum of the condition.
		Can be CONDITION_TYPE enum of NONE, NOT, AND, OR
		*/

	BOOLEAN setLeftAstNode(AST_NODE_PTR left_node_ptr);
		/*
		Description: Returns True if able to set left_node_ as left_node_ptr, false otherwise.
		left_node_ptr must be ConditionNode or RelationNode
		*/

	BOOLEAN setRightAstNode(AST_NODE_PTR right_node_ptr);
		/*
		Description: Returns True if able to set right_node_ as right_node_ptr, false otherwise.
		right_node_ptr must be ConditionNode or RelationNode
		*/

	CONDITION_TYPE getConditionType();
		/*
		Description: Returns the CONDITION_TYPE of this condition.
		*/

	AST_NODE_PTR getLeftAstNode();
		/*
		Description: Returns the AST_NODE_PTR of the left hand side of the expression.
		*/

	AST_NODE_PTR getRightAstNode();
		/*
		Description: Returns the AST_NODE_PTR of the right hand side of the expression, throws exception if this node has CONDITION_TYPE NONE.
		*/

private:
	CONDITION_TYPE condition_type_;
	AST_NODE_PTR left_node_ptr_;
	AST_NODE_PTR right_node_ptr_;

};

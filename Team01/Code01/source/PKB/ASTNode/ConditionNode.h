#pragma once

#include <memory>
#include <string>
#include "ASTNode.h"
#include "VariableNode.h"
#include "ConditionTypeEnum.h"

typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef ConditionTypeEnum CONDITION_TYPE;
typedef bool BOOLEAN;

class ConditionNode : public StatementNode {

public:
	ConditionNode(CONDITION_TYPE condition_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr);
		/*
		Description: Constructs a ConditionNode with the CONDITION_TYPE including the left child 
		AST_NODE_PTR and right child AST_NODE_PTR of this CondtiionNode.
		*/

	BOOLEAN setConditionType(CONDITION_TYPE condition_type);
		/*
		Description: Returns True if able to set the CONDITION_TYPE of this ConditionNode, false otherwise.
		*/

	BOOLEAN setLeftAstNode(AST_NODE_PTR left_node_ptr);
		/*
		Description: Returns True if able to set AST_NODE_PTR to be the left-hand side child of this Condition, false otherwise
		*/

	BOOLEAN setRightAstNode(AST_NODE_PTR right_node_ptr);
		/*
		Description: Returns True if able to set AST_NODE_PTR to be the right-hand side child of this Condition, false otherwise.
		*/

	CONDITION_TYPE getConditionType();
		/*
		Description: Returns the CONDITION_TYPE of this ConditionNode
		*/

	AST_NODE_PTR getLeftAstNode();
		/*
		Description: Returns the left-hand side child AST_NODE_PTR of this Condition.
		*/

	AST_NODE_PTR getRightAstNode();
		/*
		Description: Returns the right-hand side child AST_NODE_PTR of this Condition.
		*/

private:
	CONDITION_TYPE condition_type_;
	AST_NODE_PTR left_node_ptr_;
	AST_NODE_PTR right_node_ptr_;

};

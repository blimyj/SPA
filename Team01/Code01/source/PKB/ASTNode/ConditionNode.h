#pragma once

#include <memory>
#include <string>
#include "RelationNode.h"
#include "StatementNode.h"
#include "ConditionTypeEnum.h"

typedef std::shared_ptr<RelationNode> RELATION_NODE_PTR;
typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef ConditionTypeEnum CONDITION_TYPE;
typedef bool BOOLEAN;

class ConditionNode : public StatementNode {
/*Condition Node is !, &&, || or none*/

public:
	ConditionNode(CONDITION_TYPE condition_type, RELATION_NODE_PTR left_relation_node_ptr, RELATION_NODE_PTR right_relation_node_ptr);
		/*
		Description: Constructs a ConditionNode with the CONDITION_TYPE including the left child 
		RELATION_NODE_PTR and right child RELATION_NODE_PTR of this CondtiionNode.
		*/

	BOOLEAN setConditionType(CONDITION_TYPE condition_type);
		/*
		Description: Returns True if able to set the CONDITION_TYPE of this ConditionNode, false otherwise.
		*/

	BOOLEAN setLeftRelationNode(RELATION_NODE_PTR leftRelationNode);
		/*
		Description: Returns True if able to set RELATION_NODE_PTR to be the left-hand side child of this Condition, false otherwise
		*/

	BOOLEAN setRightRelationNode(RELATION_NODE_PTR rightRelationNode);
		/*
		Description: Returns True if able to set RELATION_NODE_PTR to be the right-hand side child of this Condition, false otherwise.
		*/

	CONDITION_TYPE getConditionType();
		/*
		Description: Returns the CONDITION_TYPE of this ConditionNode
		*/

	RELATION_NODE_PTR getLeftRelationNode();
		/*
		Description: Returns the left-hand side child RELATION_NODE_PTR of this Condition.
		*/

	RELATION_NODE_PTR getRightRelationNode();
		/*
		Description: Returns the right-hand side child RELATION_NODE_PTR of this Condition.
		*/

private:
	CONDITION_TYPE condition_type_;
	RELATION_NODE_PTR left_relation_node_ptr_;
	RELATION_NODE_PTR right_relation_node_ptr_;

};

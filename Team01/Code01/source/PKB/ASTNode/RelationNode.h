#pragma once

#include <memory>
#include <string>

#include "ASTNode.h"
#include "RelationTypeEnum.h"

typedef std::shared_ptr<ASTNode> AST_NODE_PTR;
typedef RelationTypeEnum RELATION_TYPE;
typedef bool BOOLEAN;

class RelationNode : public ASTNode {
/*RelationNode is ==, !=, <=, >=, <, >*/

public:
	RelationNode(RELATION_TYPE relation_type, AST_NODE_PTR left_node_ptr, AST_NODE_PTR right_node_ptr);
		/*
		Description: Constructs a RelationNode with the RELATION_TYPE, including the left child AST_NODE_PTR and right child AST_NODE_PTR of this Relation.
		*/

	BOOLEAN setRelationType(RELATION_TYPE relation_type);
		/*
		Description: Returns True if able to set the RELATION_TYPE of this relation, false otherwise.
		*/

	BOOLEAN setLeftAstNode(AST_NODE_PTR left_node_ptr);
		/*
		Description: Returns True if able to set AST_NODE_PTR to be the left-hand side child of this Relation, false otherwise
		*/

	BOOLEAN setRightAstNode(AST_NODE_PTR right_node_ptr);
		/*
		Description: Returns True if able to set AST_NODE_PTR to be the right-hand side child of this Relation, false otherwise.
		*/

	RELATION_TYPE getRelationType();
		/*
		Description: Returns the RELATION_TYPE of this ExpressionNode
		*/

	AST_NODE_PTR getLeftAstNode();
		/*
		Description: Returns the left-hand side child AST_NODE_PTR of this Relation.
		*/

	AST_NODE_PTR getRightAstNode();
		/*
		Description: Returns the right-hand side child AST_NODE_PTR of this Relation.
		*/

private:
	RELATION_TYPE relation_type_;
	AST_NODE_PTR left_node_ptr_;
	AST_NODE_PTR right_node_ptr_;

};

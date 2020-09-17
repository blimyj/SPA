#pragma once

#include <memory>
#include "ExpressionNode.h"
#include "StatementNode.h"
#include "VariableNode.h"

typedef std::shared_ptr<ExpressionNode> EXPR_NODE_PTR;
typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef bool BOOLEAN;

class AssignNode : public StatementNode {

public:
	AssignNode(VAR_NODE_PTR var_node_ptr, EXPR_NODE_PTR expr_node_ptr);
		/*
		Description: Constructs an AssignNode with the children VAR_NODE_PTR and EXPR_NODE_PTR.
		*/

	BOOLEAN setVariableNode(VAR_NODE_PTR var_node_ptr);
		/*
		Description: Returns True if able to set VAR_NODE_PTR as a child of this AssignNode, false otherwise
		*/

	BOOLEAN setExpressionNode(EXPR_NODE_PTR expr_node_ptr);
		/*
		Description: Returns True if able to set EXPR_NODE_PTR as a child of this AssignNode, false otherwise
		*/

	VAR_NODE_PTR getVariableNode();
		/*
		Description: Returns the child VAR_NODE_PTR of this AssignNode
		*/

	EXPR_NODE_PTR getExpressionNode();
		/*
		Description: Returns the child EXPR_NODE_PTR of this AssignNode
		*/

private:
	VAR_NODE_PTR var_node_ptr_;
	EXPR_NODE_PTR expr_node_ptr_;

};

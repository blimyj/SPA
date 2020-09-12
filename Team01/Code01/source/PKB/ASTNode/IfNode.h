#pragma once

#include <memory>
#include "ConditionNode.h"
#include "StatementListNode.h"
#include "StatementNode.h"

typedef std::shared_ptr<ConditionNode> CONDITION_NODE_PTR;
typedef std::shared_ptr<StatementListNode> STMT_LIST_NODE_PTR;
typedef bool BOOLEAN;

class IfNode : public StatementNode {
public:
	IfNode(CONDITION_NODE_PTR condition_node_ptr, STMT_LIST_NODE_PTR then_stmt_list_node_ptr, STMT_LIST_NODE_PTR else_stmt_list_node_ptr);
		/*
		Description: Constructs a IfNode with the child CONDITION_NODE_PTR and \
		following then STMT_LIST_NODE_PTR and else STMT_LIST_NODE_PTR.
		*/

	BOOLEAN setConditionNode(CONDITION_NODE_PTR condition_node_ptr);
		/*
		Description: Returns True if able to set the 
		CONDITION_NODE_PTR of this if statement.
		*/

	BOOLEAN setThenStatementListNode(STMT_LIST_NODE_PTR then_stmt_list_node_ptr);
		/*
		Description: Returns True if able to set the then child 
		STMT_LIST_NODE_PTR of this if statement.
		*/

	BOOLEAN setElseStatementListNode(STMT_LIST_NODE_PTR else_stmt_list_node_ptr);
		/*
		Description: Returns True if able to set the else child 
		STMT_LIST_NODE_PTR of this if statement.
		*/
	CONDITION_NODE_PTR getConditionNode();
		/*
		Description: Returns the CODITION_NODE_PTR of this if statement.
		*/

	STMT_LIST_NODE_PTR getThenStatementListNode();
		/*
		Description: Returns the then child STMT_LIST_NODE_PTR of this if statement
		*/

	STMT_LIST_NODE_PTR getElseStatementListNode();
		/*
		Description: Returns the else child STMT_LIST_NODE_PTR of this if statement
		*/

private:
	CONDITION_NODE_PTR condition_node_ptr_;
	STMT_LIST_NODE_PTR then_stmt_list_node_ptr_;
	STMT_LIST_NODE_PTR else_stmt_list_node_ptr_;

};

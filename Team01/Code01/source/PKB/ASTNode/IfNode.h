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
		Description: Constructs an IfNode with the given CONDITION_NODE_PTR, STATEMENT_LIST_PTR for both then and else.
		*/

	BOOLEAN setConditionNode(CONDITION_NODE_PTR condition_node_ptr);
		/*
		Description: Returns True if able to set the condition_node_ptr_ as condition_node_ptr  of IfNode condition.
		*/

	BOOLEAN setThenStatementListNode(STMT_LIST_NODE_PTR then_stmt_list_node_ptr);
		/*
		Description: Returns True if able to set then_stmt_list_node_ as then_stmt_list, false otherwise.
		*/

	BOOLEAN setElseStatementListNode(STMT_LIST_NODE_PTR else_stmt_list_node_ptr);
		/*
		Description: Returns True if able to set else_stmt_list_node_ as else_stmt_list, false otherwise.
		*/
	CONDITION_NODE_PTR getConditionNode();
		/*
		Description: Returns the CONDITION_NODE_PTR of IfNode condition.
		*/

	STMT_LIST_NODE_PTR getThenStatementListNode();
		/*
		Description: Returns a STATEMENT_LIST_NODE_PTR of the then statement body.
		*/

	STMT_LIST_NODE_PTR getElseStatementListNode();
		/*
		Description: Returns a STATEMENT_LIST_NODE_PTR of the else statement body.
		*/

private:
	CONDITION_NODE_PTR condition_node_ptr_;
	STMT_LIST_NODE_PTR then_stmt_list_node_ptr_;
	STMT_LIST_NODE_PTR else_stmt_list_node_ptr_;

};

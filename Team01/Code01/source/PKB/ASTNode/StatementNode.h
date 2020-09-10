#pragma once

class StatementNode;

#include <memory>
#include "ASTNode.h"
#include "StatementListNode.h"

typedef std::shared_ptr<StatementListNode> STMT_LIST_NODE_PTR;
typedef bool BOOLEAN;
typedef int STMT_NUMBER;

class StatementNode : public ASTNode {
	BOOLEAN setStatementNumber(STMT_NUMBER stmt_num);
		/*
		Description: Returns true if successfully setting the STMT_NUMBER of this StatementNode.
		*/

	BOOLEAN setStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr);
		/*
		Description: Returns true if successfully setting the STMT_LIST_NODE of this StatementNode.
		*/

	STMT_NUMBER getStatementNumber();
		/*
		Description: Returns STMT_NUMBER of this statement.
		*/

	STMT_LIST_NODE_PTR getParentStatementListNode();
		/*
		Description: Returns the parent STMT_LIST_NODE_PTR of this StatementNode.
		*/

private:
	STMT_NUMBER stmt_num_;
	STMT_LIST_NODE_PTR stmt_list_node_ptr_;

};
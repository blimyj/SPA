#pragma once

class StatementNode;

#include <memory>
#include "ASTNode.h"
#include "StatementListNode.h"

typedef std::shared_ptr<StatementListNode> STMT_LIST_NODE_PTR;
typedef bool BOOLEAN;
typedef int STMT_NUM;

class StatementNode : public ASTNode {

public:
	BOOLEAN setStatementNumber(STMT_NUM stmt_num);
		/*
		Description: Returns True if able to set a STMT_NUM of this StatementNode.
		*/

	BOOLEAN setStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr);
		/*
		Description: Returns True if able to set the STMT_LIST_NODE_PTR that contains this StatementNode.
		*/

	STMT_NUM getStatementNumber();
		/*
		Description: Returns the STMT_NUM of this StatementNode.
		*/

	STMT_LIST_NODE_PTR getParentStatementListNode();
		/*
		Description: Returns the STMT_LIST_NODE_PTR that contains this StatementNode.
		*/

private:
	STMT_NUM stmt_num_;
	STMT_LIST_NODE_PTR stmt_list_node_ptr_;

};
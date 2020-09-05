#pragma once

#include "ASTNode.h"

class StatementNode : public ASTNode {
	BOOLEAN setStatementNumber(INDEX stmt_num);
		/*
		Description: Returns true if successfully setting the INDEX of the statement index of this StatementNode.
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

};
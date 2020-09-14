#pragma once

class StatementListNode;

#include <memory>
#include <vector>
#include "ASTNode.h"
#include "StatementNode.h"

typedef std::shared_ptr<StatementNode> STMT_NODE_PTR;
typedef std::vector<std::shared_ptr<StatementNode>> STMT_NODE_PTR_LIST;
typedef bool BOOLEAN;

class StatementListNode : public ASTNode {

public:
	StatementListNode();
		/*
		Description: Constructs an empty StatementListNode.
		*/

	BOOLEAN addStatementNode(STMT_NODE_PTR stmt_node_ptr);
		/*
		Description: Returns True if able to add a child STMT_NODE_PTR of the statement list, false otherwise.
		*/

	STMT_NODE_PTR_LIST getStatementNodeList();
		/*
		Description: Returns the list of children, TMT_NODE_PTR_LIST, of the statement list.
		*/

private:
	STMT_NODE_PTR_LIST stmt_node_ptr_list_;

};

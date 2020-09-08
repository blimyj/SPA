typedef std::shared_ptr<ConditionNode> CONDITION_NODE_PTR;
typedef std::shared_ptr<StatementListNode> STMT_LIST_NODE_PTR;
typedef bool BOOLEAN;

#include <iostream>
#include "ConditionNode.h"
#include "StatementListNode.h"
#include "WhileNode.h"

WhileNode::WhileNode(CONDITION_NODE_PTR condition_node_ptr, STMT_LIST_NODE_PTR stmt_list_node_ptr) {
	setConditionNode(condition_node_ptr);
	setWhileStatementListNode(stmt_list_node_ptr);
}

BOOLEAN WhileNode::setConditionNode(CONDITION_NODE_PTR condition_node_ptr) {
	try {
		condition_node_ptr_ = condition_node_ptr;
	} catch (int e) {
		return false;
	}
	return true;
}

BOOLEAN WhileNode::setWhileStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr) {
	try {
		stmt_list_node_ptr_ = stmt_list_node_ptr;
	} catch (int e) {
		return false;
	}
	return true;
}

CONDITION_NODE_PTR WhileNode::getConditionNode() {
	return condition_node_ptr_;
}

STMT_LIST_NODE_PTR WhileNode::getWhileStatementListNode() {
	return stmt_list_node_ptr_;
}



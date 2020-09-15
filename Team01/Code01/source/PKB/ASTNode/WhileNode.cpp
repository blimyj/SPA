#include "WhileNode.h"

WhileNode::WhileNode() {
	node_type_ = { NODE_TYPE::whileNode };
	condition_node_ptr_ = nullptr;
	while_stmt_list_node_ptr_ = nullptr;
}

BOOLEAN WhileNode::setConditionNode(CONDITION_NODE_PTR condition_node_ptr) {
	try {
		if (condition_node_ptr == nullptr) {
			return false;
		}
		addChildNode(condition_node_ptr);
		condition_node_ptr->setParentNode(shared_from_this());
		condition_node_ptr_ = condition_node_ptr;
	} catch (int e) {
		(void)e;
		return false;
	}
	return true;
}

BOOLEAN WhileNode::setWhileStatementListNode(STMT_LIST_NODE_PTR while_stmt_list_node_ptr) {
	try {
		if (while_stmt_list_node_ptr == nullptr) {
			return false;
		}
		addChildNode(while_stmt_list_node_ptr);
		while_stmt_list_node_ptr->setParentNode(shared_from_this());
		while_stmt_list_node_ptr_ = while_stmt_list_node_ptr;
	} catch (int e) {
		(void)e;
		return false;
	}
	return true;
}

CONDITION_NODE_PTR WhileNode::getConditionNode() {
	return condition_node_ptr_;
}

STMT_LIST_NODE_PTR WhileNode::getWhileStatementListNode() {
	return while_stmt_list_node_ptr_;
}



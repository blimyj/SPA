#include "WhileNode.h"

WhileNode::WhileNode() {
	node_type_ = { NODE_TYPE::whileNode };
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

BOOLEAN WhileNode::setWhileStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr) {
	try {
		if (stmt_list_node_ptr == nullptr) {
			return false;
		}
		addChildNode(stmt_list_node_ptr);
		stmt_list_node_ptr->setParentNode(shared_from_this());
		stmt_list_node_ptr_ = stmt_list_node_ptr;
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
	return stmt_list_node_ptr_;
}



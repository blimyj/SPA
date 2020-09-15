#include "WhileNode.h"

WhileNode::WhileNode(CONDITION_NODE_PTR condition_node_ptr, STMT_LIST_NODE_PTR stmt_list_node_ptr) {
	setConditionNode(condition_node_ptr);
	setWhileStatementListNode(stmt_list_node_ptr);
	node_type_ = { NODE_TYPE::whileNode };
}

BOOLEAN WhileNode::setConditionNode(CONDITION_NODE_PTR condition_node_ptr) {
	try {
		addChildNode(condition_node_ptr);
		condition_node_ptr->setParentNode(std::make_shared<WhileNode>(*this));
		condition_node_ptr_ = condition_node_ptr;
	} catch (int e) {
		(void)e;
		return false;
	}
	return true;
}

BOOLEAN WhileNode::setWhileStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr) {
	try {
		addChildNode(stmt_list_node_ptr);
		stmt_list_node_ptr->setParentNode(std::make_shared<WhileNode>(*this));
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



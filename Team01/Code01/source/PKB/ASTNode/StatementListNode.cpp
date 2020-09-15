#include "StatementListNode.h"

StatementListNode::StatementListNode() {
    node_type_ = { NODE_TYPE::statementListNode };
}

BOOLEAN StatementListNode::addStatementNode(STMT_NODE_PTR stmt_node_ptr) {
    try {
        addChildNode(stmt_node_ptr);
        stmt_node_ptr->setParentNode(std::make_shared<StatementListNode>(*this));
        stmt_node_ptr_list_.push_back(stmt_node_ptr);
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

STMT_NODE_PTR_LIST StatementListNode::getStatementNodeList() {
    return stmt_node_ptr_list_;
}

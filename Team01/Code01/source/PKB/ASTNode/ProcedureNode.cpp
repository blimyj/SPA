#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(STRING proc_name, STMT_LIST_NODE_PTR stmt_list_node_ptr) {
    setProcedureName(proc_name);
    setProcedureStatementListNode(stmt_list_node_ptr);
    node_type_ = { NODE_TYPE::procedureNode };
}

BOOLEAN ProcedureNode::setProcedureName(STRING proc_name) {
    try {
        proc_name_ = proc_name;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN ProcedureNode::setProcedureStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr) {
    try {
        if (stmt_list_node_ptr == nullptr) {
            return false;
        }
        addChildNode(stmt_list_node_ptr);
        stmt_list_node_ptr->setParentNode(std::make_shared<ProcedureNode>(*this));
        stmt_list_node_ptr_ = stmt_list_node_ptr;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

STRING ProcedureNode::getProcedureName() {
    return proc_name_;
}

STMT_LIST_NODE_PTR ProcedureNode::getProcedureStatementListNode() {
    return stmt_list_node_ptr_;
}

#include "ProcedureNode.h"

ProcedureNode::ProcedureNode(STRING proc_name, STMT_LIST_NODE_PTR stmt_list_node_ptr) {
    setProcedureName(proc_name);
    setProcedureStatementListNode(stmt_list_node_ptr);
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
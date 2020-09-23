#include "ProcedureNode.h"

ProcedureNode::ProcedureNode() {
    node_type_ = { NODE_TYPE::procedureNode };
    proc_name_ = "";
    proc_stmt_list_node_ptr_ = nullptr;
}

BOOLEAN_TYPE ProcedureNode::setProcedureName(STRING proc_name) {
    try {
        proc_name_ = proc_name;
    } catch (int e) {
        (void)e;
        return false;
    }
    return true;
}

BOOLEAN_TYPE ProcedureNode::setProcedureStatementListNode(STMT_LIST_NODE_PTR proc_stmt_list_node_ptr) {
    try {
        if (proc_stmt_list_node_ptr == nullptr) {
            return false;
        }
        addChildNode(proc_stmt_list_node_ptr);
        std::shared_ptr<ProcedureNode> sp = shared_from_this();
        proc_stmt_list_node_ptr->setParentNode(sp);
        proc_stmt_list_node_ptr_ = proc_stmt_list_node_ptr;
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
    return proc_stmt_list_node_ptr_;
}

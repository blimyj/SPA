#include "ProcedureTable.h"

INDEX ProcedureTable::addProcedureNode(PROC_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

PROC_NODE_PTR_LIST ProcedureTable::getProcedureNodeList() {
    return PROC_NODE_PTR_LIST(nodes_);
}

PROC_NAME_LIST ProcedureTable::getProcedureNameList() {
    std::vector<PROC_NAME> result;
    for (PROC_NODE_PTR n : nodes_) {
        PROC_NAME p = n.get()->getProcedureName();
        result.push_back(p);
    }
    return result;
}

#include "ProcedureTable.h"

INDEX ProcedureTable::addProcedureNode(PROC_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

PROC_NODE_PTR_LIST ProcedureTable::getProcedureNodeList() {
    PROC_NODE_PTR_LIST copy;
    for (PROC_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}

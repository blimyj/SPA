typedef int INDEX;
typedef std::shared_ptr<ProcedureNode> PROC_NODE_PTR;
typedef std::vector<PROC_NODE_PTR> TABLE;
typedef std::vector<PROC_NODE_PTR> PROC_NODE_PTR_LIST;

#include <iostream>
#include <vector>
#include "ProcedureTable.h"
#include "../ASTNode/ProcedureNode.h"

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

#include "WhileTable.h"

INDEX WhileTable::addWhileNode(WHILE_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

WHILE_NODE_PTR_LIST WhileTable::getWhileNodeList() {
    WHILE_NODE_PTR_LIST copy;
    for (WHILE_NODE_PTR node : nodes_) {
        copy.push_back(node);
    }
    return copy;
}

STMT_NUM_LIST WhileTable::getWhileNumList() {
    std::vector<STMT_NUM> result;
    for (WHILE_NODE_PTR n : nodes_) {
        STMT_NUM s = n.get()->getStatementNumber();
        result.push_back(s);
    }
    return result;
}

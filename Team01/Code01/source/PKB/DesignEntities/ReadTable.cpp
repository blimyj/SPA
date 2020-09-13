#include "ReadTable.h"

INDEX ReadTable::addReadNode(READ_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

READ_NODE_PTR_LIST ReadTable::getReadNodeList() {
    READ_NODE_PTR_LIST copy;
    for (READ_NODE_PTR node : nodes_) {
        copy.push_back(node);
    }
    return copy;
}

STMT_NUM_LIST ReadTable::getReadNumList() {
    std::vector<STMT_NUM> result;
    for (READ_NODE_PTR n : nodes_) {
        STMT_NUM s = n.get()->getStatementNumber();
        result.push_back(s);
    }
    return result;
}

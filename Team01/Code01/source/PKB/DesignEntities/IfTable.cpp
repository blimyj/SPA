#include "IfTable.h"

INDEX IfTable::addIfNode(IF_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

IF_NODE_PTR_LIST IfTable::getIfNodeList() {
    return IF_NODE_PTR_LIST(nodes_);
}

STMT_NUM_LIST IfTable::getIfNumList() {
    std::vector<STMT_NUM> result;
    for (IF_NODE_PTR n : nodes_) {
        STMT_NUM s = n.get()->getStatementNumber();
        result.push_back(s);
    }
    return result;
}

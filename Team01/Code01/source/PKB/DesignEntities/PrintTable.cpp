#include "PrintTable.h"

INDEX PrintTable::addPrintNode(PRINT_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

PRINT_NODE_PTR_LIST PrintTable::getPrintNodeList() {
    PRINT_NODE_PTR_LIST copy;
    for (PRINT_NODE_PTR node : nodes_) {
        copy.push_back(node);
    }
    return copy;
}

STMT_NUM_LIST PrintTable::getPrintNumList() {
    std::vector<STMT_NUM> result;
    for (PRINT_NODE_PTR n : nodes_) {
        STMT_NUM s = n.get()->getStatementNumber();
        result.push_back(s);
    }
    return result;
}

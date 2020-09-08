#include "PrintTable.h"

INDEX PrintTable::addPrintNode(PRINT_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

PRINT_NODE_PTR_LIST PrintTable::getPrintNodeList() {
    PRINT_NODE_PTR_LIST copy;
    for (PRINT_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}

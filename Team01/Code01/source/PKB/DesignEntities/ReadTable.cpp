#include "ReadTable.h"

INDEX ReadTable::addReadNode(READ_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

READ_NODE_PTR_LIST ReadTable::getReadNodeList() {
    READ_NODE_PTR_LIST copy;
    for (READ_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}

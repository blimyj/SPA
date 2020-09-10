#include "IfTable.h"

INDEX IfTable::addIfNode(IF_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

IF_NODE_PTR_LIST IfTable::getIfNodeList() {
    IF_NODE_PTR_LIST copy;
    for (IF_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}

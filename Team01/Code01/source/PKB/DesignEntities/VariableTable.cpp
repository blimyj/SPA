#include "VariableTable.h"

INDEX VariableTable::addVariableNode(VAR_NODE_PTR node) {
    INDEX index = table_.size();
    table_.push_back(node);
    return index;
}

VAR_NODE_PTR_LIST VariableTable::getVariableNodeList() {
    VAR_NODE_PTR_LIST copy;
    for (VAR_NODE_PTR node : table_) {
        copy.push_back(node);
    }
    return copy;
}

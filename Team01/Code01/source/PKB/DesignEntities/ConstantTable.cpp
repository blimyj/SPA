#include "ConstantTable.h"

INDEX ConstantTable::addConstantNode(CONSTANT_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

CONSTANT_NODE_PTR_LIST ConstantTable::getConstantNodeList() {
    CONSTANT_NODE_PTR_LIST copy;
    for (CONSTANT_NODE_PTR node : nodes_) {
        copy.push_back(node);
    }
    return copy;
}

CONSTANT_VALUE_LIST ConstantTable::getConstantValueList() {
    std::vector<CONSTANT_VALUE> result;
    for (CONSTANT_NODE_PTR n : nodes_) {
        // TODO: ConstantNode.h
        // Change constant value from int to string to prevent overflows
        int v = n.get()->getValue();
        CONSTANT_VALUE c = std::to_string(v);
        result.push_back(c);
    }
    return result;
}

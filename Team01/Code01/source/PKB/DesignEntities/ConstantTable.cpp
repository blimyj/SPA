#include <unordered_set>
#include "ConstantTable.h"

INDEX ConstantTable::addConstantNode(CONSTANT_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

CONSTANT_NODE_PTR_LIST ConstantTable::getConstantNodeList() {
    return CONSTANT_NODE_PTR_LIST(nodes_);
}

CONSTANT_VALUE_LIST ConstantTable::getConstantValueList() {
    std::unordered_set<CONSTANT_VALUE> set;
    for (CONSTANT_NODE_PTR n : nodes_) {
        VALUE v = n.get()->getValue();
        set.insert(v);
    }
    return CONSTANT_VALUE_LIST(set.begin(), set.end());
}

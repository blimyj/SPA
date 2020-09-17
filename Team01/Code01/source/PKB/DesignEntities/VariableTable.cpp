#include <unordered_set>
#include "VariableTable.h"

INDEX VariableTable::addVariableNode(VAR_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

VAR_NODE_PTR_LIST VariableTable::getVariableNodeList() {
    return VAR_NODE_PTR_LIST(nodes_);
}

VAR_NAME_LIST VariableTable::getVariableNameList() {
    std::unordered_set<VAR_NAME> set;
    for (VAR_NODE_PTR n : nodes_) {
        VAR_NAME v = n.get()->getVariableName();
        set.insert(v);
    }
    return VAR_NAME_LIST(set.begin(), set.end());
}

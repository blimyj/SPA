#include "VariableTable.h"

INDEX VariableTable::addVariableNode(VAR_NODE_PTR node) {
    INDEX index = nodes_.size();
    nodes_.push_back(node);
    return index;
}

VAR_NODE_PTR_LIST VariableTable::getVariableNodeList() {
    VAR_NODE_PTR_LIST copy;
    for (VAR_NODE_PTR node : nodes_) {
        copy.push_back(node);
    }
    return copy;
}

VAR_NAME_LIST VariableTable::getVariableNameList() {
    std::vector<VAR_NAME> result;
    for (VAR_NODE_PTR n : nodes_) {
        VAR_NAME v = n.get()->getVariableName();
        result.push_back(v);
    }
    return result;
}

#include <iostream>
#include <vector>
#include "ReadTable.h"
#include "../ASTNode/ReadNode.h"

typedef int INDEX;
typedef ReadNode* READ_NODE_PTR;
typedef std::vector<READ_NODE_PTR> TABLE;
typedef std::vector<READ_NODE_PTR> READ_NODE_PTR_LIST;

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

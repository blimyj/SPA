typedef int INDEX;
typedef std::shared_ptr<PrintNode> PRINT_NODE_PTR;
typedef std::vector<PRINT_NODE_PTR> TABLE;
typedef std::vector<PRINT_NODE_PTR> PRINT_NODE_PTR_LIST;

#include <iostream>
#include <vector>
#include "PrintTable.h" 
#include "../ASTNode/PrintNode.h" 

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

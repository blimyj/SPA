#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/WhileNode.h"

typedef int INDEX;
typedef std::shared_ptr<WhileNode> WHILE_NODE_PTR;
typedef std::vector<WHILE_NODE_PTR> TABLE;
typedef std::vector<WHILE_NODE_PTR> WHILE_NODE_PTR_LIST;

class WhileTable {
/* Overview: This is a data structure*/

public:
    INDEX addWhileNode(WHILE_NODE_PTR node);
        /*
        Description: Returns the index of the WHILE_NODE_PTR added to the table.
        */

    WHILE_NODE_PTR_LIST getWhileNodeList();
        /*
        Description: Returns a WHILE_NODE_PTR_LIST of the table.
        */

private:
    TABLE table_;

};

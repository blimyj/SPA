#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/ConstantNode.h"

typedef int INDEX;
typedef std::shared_ptr<ConstantNode> CONSTANT_NODE_PTR;
typedef std::vector<CONSTANT_NODE_PTR> CONSTANT_NODE_PTR_LIST;

class ConstantTable {
/* Overview: This is a data structure*/

public:
    INDEX addConstantNode(CONSTANT_NODE_PTR node);
        /*
        Description: Returns the index of the CONSTANT_NODE_PTR added to the table.
        */

    CONSTANT_NODE_PTR_LIST getConstantNodeList();
        /*
        Description: Returns a CONSTANT_NAME_PTR_LIST of the table.
        */

private:
    CONSTANT_NODE_PTR_LIST table_;

};

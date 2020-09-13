#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../ASTNode/ConstantNode.h"

typedef int INDEX;
typedef std::string CONSTANT_VALUE;
typedef std::shared_ptr<ConstantNode> CONSTANT_NODE_PTR;
typedef std::vector<CONSTANT_NODE_PTR> CONSTANT_NODE_PTR_LIST;
typedef std::vector<CONSTANT_VALUE> CONSTANT_VALUE_LIST;

class ConstantTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    INDEX addConstantNode(CONSTANT_NODE_PTR node);
        /*
        Description: Returns the index of the CONSTANT_NODE_PTR added to the table.
        */

    CONSTANT_NODE_PTR_LIST getConstantNodeList();
        /*
        Description: Returns a CONSTANT_NAME_PTR_LIST of the table.
        */

    CONSTANT_VALUE_LIST getConstantValueList();
        /*
        Description: Returns a CONSTANT_VALUE_LIST of the table.
        */

    std::vector<CONSTANT_NODE_PTR> nodes_;

};

#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/VariableNode.h"

typedef int INDEX;
typedef std::string VAR_NAME;
typedef std::shared_ptr<VariableNode> VAR_NODE_PTR;
typedef std::vector<VAR_NODE_PTR> VAR_NODE_PTR_LIST;
typedef std::vector<VAR_NAME> VAR_NAME_LIST;

class VariableTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    INDEX addVariableNode(VAR_NODE_PTR node);
        /*
        Description: Returns the index of the VAR_NODE_PTR added to the table.
        */

    VAR_NODE_PTR_LIST getVariableNodeList();
        /*
        Description: Returns a VAR_NODE_PTR_LIST of the table.
        */

    VAR_NAME_LIST getVariableNameList();
        /*
        Description: Returns a VAR_NAME_LIST of the table.
        */

    std::vector<VAR_NODE_PTR> nodes_;
};

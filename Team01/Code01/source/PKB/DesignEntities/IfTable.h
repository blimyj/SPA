#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/IfNode.h"

typedef int INDEX;
typedef std::shared_ptr<IfNode> IF_NODE_PTR;
typedef std::vector<IF_NODE_PTR> IF_NODE_PTR_LIST;
typedef std::vector<STMT_NUM> STMT_NUM_LIST;

class IfTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    INDEX addIfNode(IF_NODE_PTR node);
        /*
        Description: Returns the index of the IF_NODE_PTR added to the table.
        */

    IF_NODE_PTR_LIST getIfNodeList();
        /*
        Description: Returns a IF_NODE_PTR_LIST of the table.
        */

    STMT_NUM_LIST getIfNumList();
        /*
        Description: Returns a STMT_NUM_LIST of the table.
        */

    std::vector<IF_NODE_PTR> nodes_;

};

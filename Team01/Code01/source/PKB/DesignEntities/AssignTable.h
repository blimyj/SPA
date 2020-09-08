#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/AssignNode.h"

typedef int INDEX;
typedef std::shared_ptr<AssignNode> ASSIGN_NODE_PTR;
typedef std::vector<ASSIGN_NODE_PTR> ASSIGN_NODE_PTR_LIST;

class AssignTable {
/* Overview: This is a data structure*/

public:
    INDEX addAssignNode(ASSIGN_NODE_PTR node);
        /*
        Description: Returns the index of the ASSIGN_NODE_PTR added to the table.
        */

    ASSIGN_NODE_PTR_LIST getAssignNodeList();
        /*
        Description: Returns a ASSIGN_NODE_PTR_LIST of the table.
        */

private:
    ASSIGN_NODE_PTR_LIST table_;

};

#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/IfNode.h"

typedef int INDEX;
typedef std::shared_ptr<IfNode> IF_NODE_PTR;
typedef std::vector<IF_NODE_PTR> IF_NODE_PTR_LIST;

class IfTable {
/* Overview: This is a data structure*/

public:
    INDEX addIfNode(IF_NODE_PTR node);
        /*
        Description: Returns the index of the IF_NODE_PTR added to the table.
        */

    IF_NODE_PTR_LIST getIfNodeList();
        /*
        Description: Returns a IF_NODE_PTR_LIST of the table.
        */

private:
    IF_NODE_PTR_LIST table_;

};

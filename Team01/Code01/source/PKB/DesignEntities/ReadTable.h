#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/ReadNode.h"

typedef int INDEX;
typedef std::shared_ptr<ReadNode> READ_NODE_PTR;
typedef std::vector<READ_NODE_PTR> READ_NODE_PTR_LIST;

class ReadTable {
/* Overview: This is a data structure*/

public:
    INDEX addReadNode(READ_NODE_PTR node);
        /*
        Description: Returns the index of the READ_NODE_PTR added to the table.
        */

    READ_NODE_PTR_LIST getReadNodeList();
        /*
        Description: Returns a READ_NODE_PTR_LIST of the table.
        */

private:
    READ_NODE_PTR_LIST table_;

};

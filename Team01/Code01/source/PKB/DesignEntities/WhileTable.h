#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/WhileNode.h"

typedef int INDEX;
typedef std::shared_ptr<WhileNode> WHILE_NODE_PTR;
typedef std::vector<WHILE_NODE_PTR> WHILE_NODE_PTR_LIST;
typedef std::vector<STMT_NUM> STMT_NUM_LIST;

class WhileTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    INDEX addWhileNode(WHILE_NODE_PTR node);
        /*
        Description: Returns the index of the WHILE_NODE_PTR added to the table.
        */

    WHILE_NODE_PTR_LIST getWhileNodeList();
        /*
        Description: Returns a WHILE_NODE_PTR_LIST of the table.
        */

    STMT_NUM_LIST getWhileNumList();
        /*
        Description: Returns a STMT_NUM_LIST of the table.
        */

    std::vector<WHILE_NODE_PTR> nodes_;

};

#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/PrintNode.h"

typedef int INDEX;
typedef std::shared_ptr<PrintNode> PRINT_NODE_PTR;
typedef std::vector<PRINT_NODE_PTR> PRINT_NODE_PTR_LIST;

class PrintTable {
/* Overview: This is a data structure*/

public:
    INDEX addPrintNode(PRINT_NODE_PTR node);
        /*
        Description: Returns the index of the PRINT_NODE_PTR added to the table.
        */

    PRINT_NODE_PTR_LIST getPrintNodeList();
        /*
        Description: Returns a PRINT_NODE_PTR_LIST of the table.
        */

private:
    PRINT_NODE_PTR_LIST table_;

};

#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/PrintNode.h"

typedef int INDEX;
typedef std::shared_ptr<PrintNode> PRINT_NODE_PTR;
typedef std::vector<PRINT_NODE_PTR> PRINT_NODE_PTR_LIST;
typedef std::vector<STMT_NUM> STMT_NUM_LIST;
typedef std::vector<VAR_NAME> VAR_NAME_LIST;

class PrintTable {
    /* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    INDEX addPrintNode(PRINT_NODE_PTR node);
    /*
    Description: Returns the index of the PRINT_NODE_PTR added to the table.
    */

    PRINT_NODE_PTR_LIST getPrintNodeList();
    /*
    Description: Returns a PRINT_NODE_PTR_LIST of the table.
    */

    STMT_NUM_LIST getPrintNumList();
    /*
    Description: Returns a STMT_NUM_LIST of the table.
    */

    VAR_NAME_LIST getPrintVarNameList();
    /*
    Description: Returns a VAR_NAME_LIST of the table.
    */

    std::vector<PRINT_NODE_PTR> nodes_;

};
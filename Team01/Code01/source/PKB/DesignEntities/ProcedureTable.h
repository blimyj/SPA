#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/ProcedureNode.h"

typedef int INDEX;
typedef std::shared_ptr<ProcedureNode> PROC_NODE_PTR;
typedef std::vector<PROC_NODE_PTR> TABLE;
typedef std::vector<PROC_NODE_PTR> PROC_NODE_PTR_LIST;

class ProcedureTable {
/* Overview: This is a data structure*/

public:
    INDEX addProcedureNode(PROC_NODE_PTR node);
        /*
        Description: Returns the index of the PROC_NODE_PTR added to the table.
        */

    PROC_NODE_PTR_LIST getProcedureNodeList();
        /*
        Description: Returns a PROC_NODE_PTR_LIST of the table.
        */

private:
    TABLE table_;

};

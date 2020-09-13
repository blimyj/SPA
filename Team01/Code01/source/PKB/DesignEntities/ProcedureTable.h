#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/ProcedureNode.h"

typedef int INDEX;
typedef std::string PROC_NAME;
typedef std::shared_ptr<ProcedureNode> PROC_NODE_PTR;
typedef std::vector<PROC_NODE_PTR> PROC_NODE_PTR_LIST;
typedef std::vector<PROC_NAME> PROC_NAME_LIST;

class ProcedureTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    INDEX addProcedureNode(PROC_NODE_PTR node);
        /*
        Description: Returns the index of the PROC_NODE_PTR added to the table.
        */

    PROC_NODE_PTR_LIST getProcedureNodeList();
        /*
        Description: Returns a PROC_NODE_PTR_LIST of the table.
        */

    PROC_NAME_LIST getProcedureNameList();
        /*
        Description: Returns a PROC_NAME_LIST of the table.
        */

    std::vector<PROC_NODE_PTR> nodes_;

};

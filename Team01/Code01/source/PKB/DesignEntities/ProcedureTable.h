#pragma once

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

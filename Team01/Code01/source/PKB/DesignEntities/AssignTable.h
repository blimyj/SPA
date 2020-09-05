#pragma once

class AssignTable {
/* Overview: This is a data structure*/

public:
    INDEX addAssignNode(ASSIGN_NODE_PTR node);
        /*
        Description: Returns the index of the STATEMENT_NUMBER that is added to the table.
        */

    ASSIGN_NODE_PTR_LIST getAssignNodeList();
        /*
        Description: Returns a collection of STATEMENT_NUMBER added to this table.
        */

private:
    TABLE table_;

};

#pragma once

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
    TABLE table_;

};

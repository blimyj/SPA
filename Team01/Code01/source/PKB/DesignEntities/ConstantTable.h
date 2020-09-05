#pragma once

class ConstantTable {
/* Overview: This is a data structure*/

public:
    INDEX addConstantNode(CONSTANT_NODE_PTR node);
        /*
        Description: Returns the index of the CONSTANT_NODE_PTR added to the table.
        */

    CONSTANT_NODE_PTR_LIST getConstantNodeList();
        /*
        Description: Returns a CONSTANT_NAME_PTR_LIST of the table.
        */

private:
    TABLE table_;

};

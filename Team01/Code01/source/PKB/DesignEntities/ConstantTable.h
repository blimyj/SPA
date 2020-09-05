#pragma once

class ConstantTable {
/* Overview: This is a data structure*/

public:
    INDEX addConstantName(CONSTANT_NODE_PTR node);
        /*
        Description: Returns the index of the CONSTANT_NAME that is added to the table.
        */

    CONSTANT_NODE_PTR_LIST getConstantNameList();
        /*
        Description: Returns a collection of CONSTANT_NAME added to this table.
        */

private:
    TABLE table_;

};

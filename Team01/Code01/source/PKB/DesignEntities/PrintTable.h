#pragma once

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
    TABLE table_;

};

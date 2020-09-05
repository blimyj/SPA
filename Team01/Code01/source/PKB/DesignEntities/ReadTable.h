#pragma once

class ReadTable {
/* Overview: This is a data structure*/

public:
    INDEX addReadNode(READ_NODE_PTR node);
        /*
        Description: Returns the index of the READ_NODE_PTR added to the table.
        */

    READ_NODE_PTR_LIST getReadNodeList();
        /*
        Description: Returns a READ_NODE_PTR_LIST of the table.
        */

private:
    TABLE table_;

};

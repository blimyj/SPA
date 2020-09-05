#pragma once

class IfTable {
/* Overview: This is a data structure*/

public:
    INDEX addIfNode(IF_NODE_PTR node);
        /*
        Description: Returns the index of the IF_NODE_PTR added to the table.
        */

    IF_NODE_PTR_LIST getIfNodeList();
        /*
        Description: Returns a IF_NODE_PTR_LIST of the table.
        */

private:
    TABLE table_;

};

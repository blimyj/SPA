#pragma once

class VariableTable {
/* Overview: This is a data structure*/

public:
    INDEX addVariableNode(VAR_NODE_PTR node);
        /*
        Description: Returns the index of the VAR_NODE_PTR added to the table.
        */

    VAR_NODE_PTR_LIST getVariableNodeList();
        /*
        Description: Returns a VAR_NODE_PTR_LIST of the table.
        */

private:
    TABLE table_;
};

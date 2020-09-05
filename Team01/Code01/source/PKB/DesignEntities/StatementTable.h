#pragma once

class StatementTable {
/* Overview: This is a data structure*/

public:
    INDEX addStatementNode(STMT_NODE_PTR node);
        /*
        Description: Returns the index of the STMT_NODE_PTR added to the table.
        */

    STMT_NODE_PTR_LIST getStatementNodeList();
        /*
        Description: Returns a STMT_NODE_PTR_LIST of the table.
        */

private:
    TABLE table_;

};

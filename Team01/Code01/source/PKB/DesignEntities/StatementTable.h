#pragma once

#include <memory>
#include <vector>
#include "../ASTNode/StatementNode.h"

typedef int INDEX;
typedef std::shared_ptr<StatementNode> STMT_NODE_PTR;
typedef std::vector<STMT_NODE_PTR> STMT_NODE_PTR_LIST;

class StatementTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    INDEX addStatementNode(STMT_NODE_PTR node);
        /*
        Description: Returns the index of the STMT_NODE_PTR added to the table.
        */

    STMT_NODE_PTR_LIST getStatementNodeList();
        /*
        Description: Returns a STMT_NODE_PTR_LIST of the table.
        */

    std::vector<STMT_NODE_PTR> nodes_;

};

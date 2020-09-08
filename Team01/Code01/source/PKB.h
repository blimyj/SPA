#pragma once

#include <memory>
#include <vector>
#include "PKB/DesignEntities/AssignTable.h"
#include "PKB/DesignEntities/ConstantTable.h"
#include "PKB/DesignEntities/IfTable.h"
#include "PKB/DesignEntities/PrintTable.h"
#include "PKB/DesignEntities/ProcedureTable.h"
#include "PKB/DesignEntities/ReadTable.h"
#include "PKB/DesignEntities/StatementTable.h"
#include "PKB/DesignEntities/VariableTable.h"
#include "PKB/DesignEntities/WhileTable.h"
#include "PKB/Relationships/FollowsTable.h"
#include "PKB/Relationships/ParentTable.h"
#include "PKB/Relationships/UsesTable.h"
#include "PKB/Relationships/ModifiesTable.h"

typedef void PKB_BUILDER;

class PKB {
/* Overview: The PKB that contains design entities and relationships of a given SIMPLE source code */

public:
    /*==== Constructor ====*/
    PKB(PKB_BUILDER builder);

    /*==== Design Entities ====*/
    STMT_NODE_PTR_LIST getStatements();
        /*
        Description: Returns the STMT_NUM_LIST stored in STATEMENT_TABLE.
                     If there are no elements in the collection, returns an empty
                     STMT_NUM_LIST.
        */

    READ_NODE_PTR_LIST getReads();
        /*
        Description: Returns the STMT_NUM_LIST stored in READ_TABLE.
                     If there are no elements in the collection, returns an empty
                     STMT_NUM_LIST.
        */

    PRINT_NODE_PTR_LIST getPrints();
        /*
        Description: Returns the STMT_NUM_LIST stored in PRINT_TABLE.
                     If there are no elements in the collection, returns an empty
                     STMT_NUM_LIST.
        */

    WHILE_NODE_PTR_LIST getWhiles();
        /*
        Description: Returns the STMT_NUM_LIST stored in WHILE_TABLE.
                     If there are no elements in the collection, returns an empty
                     STMT_NUM_LIST.
        */

    IF_NODE_PTR_LIST getIfs();
        /*
        Description: Returns the STMT_NUM_LIST stored in IF_TABLE.
                     If there are no elements in the collection, returns an empty
                     STMT_NUM_LIST.
        */

    ASSIGN_NODE_PTR_LIST getAssigns();
        /*
        Description: Returns the STMT_NUM_LIST stored in ASSIGN_TABLE.
                     If there are no elements in the collection, returns an empty
                     STMT_NUM_LIST.
        */

    CONSTANT_NODE_PTR_LIST getConstants();
        /*
        Description: Returns the CONSTANT_NAME_LIST stored in CONSTANT_TABLE.
                     If there are no elements in the collection, returns an empty
                     CONSTANT_NAME_LIST.
        */

    VAR_NODE_PTR_LIST getVariables();
        /*
        Description: Returns the VAR_NAME_LIST stored in VARIABLE_TABLE.
                     If there are no elements in the collection, returns an empty
                     VAR_NAME_LIST.
        */

    PROC_NODE_PTR_LIST getProcedures();
        /*
        Description: Returns the PROC_NAME_LIST stored in PROCEDURE_TABLE.
                     If there are no elements in the collection, returns an empty
                     PROC_NAME_LIST.
        */

    /*==== Relationships ====*/
    BOOLEAN isFollows(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Follows(STMT_NUM, STMT_NUM) holds
        */

    BOOLEAN isParent(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Parent(STMT_NUM, STMT_NUM) holds
        */

    BOOLEAN isUses(STMT_NUM s, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Uses(STMT_NUM, VAR_NAME) holds
        */

    BOOLEAN isUses(PROC_NAME p, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Uses(PROC_NAME, VAR_NAME) holds
        */

    BOOLEAN isModifies(STMT_NUM s, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Modifies(STMT_NUM, VAR_NAME) holds
        */

    BOOLEAN isModifies(PROC_NAME p, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Modifies(PROC_NAME, VAR_NAME) holds
        */

    /*==== AST ====*/
    AST_NODE_PTR getProgramAST();
        /*
        Description: Returns the source program's AST.
        */
};

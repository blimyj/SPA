#pragma once

class PKBBuilder;

#include "PKB.h"
#include "PKB/ASTNode/ProgramNode.h"
#include "PKB/DesignEntities/AssignTable.h"
#include "PKB/DesignEntities/ConstantTable.h"
#include "PKB/DesignEntities/IfTable.h"
#include "PKB/DesignEntities/PrintTable.h"
#include "PKB/DesignEntities/ProcedureTable.h"
#include "PKB/DesignEntities/ReadTable.h"
#include "PKB/DesignEntities/StatementListTable.h"
#include "PKB/DesignEntities/StatementTable.h"
#include "PKB/DesignEntities/VariableTable.h"
#include "PKB/DesignEntities/WhileTable.h"
#include "PKB/Relationships/FollowsTable.h"
#include "PKB/Relationships/ParentTable.h"
#include "PKB/Relationships/UsesTable.h"
#include "PKB/Relationships/ModifiesTable.h"

typedef std::shared_ptr<ProgramNode> PROGRAM_NODE_PTR;

typedef AssignTable ASSIGN_TABLE;
typedef ConstantTable CONSTANT_TABLE;
typedef IfTable IF_TABLE;
typedef PrintTable PRINT_TABLE;
typedef ProcedureTable PROC_TABLE;
typedef ReadTable READ_TABLE;
typedef StatementListTable STMT_LIST_TABLE;
typedef StatementTable STMT_TABLE;
typedef VariableTable VAR_TABLE;
typedef WhileTable WHILE_TABLE;

typedef FollowsTable FOLLOWS_TABLE;
typedef ParentTable PARENT_TABLE;
typedef UsesTable USES_TABLE;
typedef ModifiesTable MODIFIES_TABLE;

class PKBBuilder {
/* Overview: A builder to aid in the construction of the PKB */

public:
    /*==== Design Entities ====*/
    INDEX addStatementNode(STMT_NODE_PTR stmt_node_ptr);
        /*
        Description: Adds a STMT_NODE_PTR to the STATEMENT_TABLE when building the PKB.
                     Returns the INDEX of the STMT_NODE_PTR in the STATEMENT_TABLE.
        */

    INDEX addStatementListNode(STMT_LIST_NODE_PTR stmt_list_node_ptr);
        /*
        Description: Adds a STMT_LIST_NODE_PTR to the STATEMENT_TABLE when building the PKB.
                     Returns the INDEX of the STMT_LIST_NODE_PTR in the STATEMENT_TABLE.
        */

    INDEX addReadNode(READ_NODE_PTR read_node_ptr);
        /*
        Description: Adds a READ_NODE_PTR to the READ_TABLE when building the PKB.
                     Returns the INDEX of the READ_NODE_PTR in the READ_TABLE.
        */

    INDEX addPrintNode(PRINT_NODE_PTR print_node_ptr);
        /*
        Description: Adds a PRINT_NODE_PTR to the PRINT_TABLE when building the PKB.
                     Returns the INDEX of the PRINT_NODE_PTR in the PRINT_TABLE.
        */

    INDEX addWhileNode(WHILE_NODE_PTR while_node_ptr);
        /*
        Description: Adds a STMT_NUM to the WHILE_TABLE when building the PKB.
                     Returns the INDEX of the STMT_NUM in the WHILE_TABLE.
        */

    INDEX addIfNode(IF_NODE_PTR if_node_ptr);
        /*
        Description: Adds a IF_NODE_PTR to the IF_TABLE when building the PKB.
                     Returns the INDEX of the IF_NODE_PTR in the IF_TABLE.
        */

    INDEX addAssignNode(ASSIGN_NODE_PTR assign_node_ptr);
        /*
        Description: Adds a ASSIGN_NODE_PTR to the ASSIGN_TABLE when building the PKB.
                     Returns the INDEX of the ASSIGN_NODE_PTR in the ASSIGN_TABLE.
        */

    INDEX addConstantNode(CONSTANT_NODE_PTR constant_node_ptr);
        /*
        Description: Adds a CONSTANT_NODE_PTR to the CONSTANT_TABLE when building the PKB.
                     Returns the INDEX of the CONSTANT_NODE_PTR in the CONSTANT_TABLE.
        */

    INDEX addVariableNode(VAR_NODE_PTR var_node_ptr);
        /*
        Description: Adds a VAR_NODE_PTR to the VARIABLE_TABLE when building the PKB.
                     Returns the INDEX of the VAR_NODE_PTR in the VARIABLE_TABLE.
        */

    INDEX addProcedureNode(PROC_NODE_PTR proc_node_ptr);
        /*
        Description: Adds a PROC_NAME to the PROCEDURE_TABLE when building the PKB.
                     Returns the INDEX of the PROC_NAME in the PROCEDURE_TABLE.
        */

    /*==== Relationships ====*/
    void addFollows(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Stores a Follows(STMT_NUM, STMT_NUM) relationship to
                     the FOLLOWS_TABLE when building the PKB.
        */
    void addParent(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Stores a Parent(STMT_NUM, STMT_NUM) relationship to
                     the PARENT_TABLE when building the PKB.
        */
    void addUses(STMT_NUM s, VAR_NAME v);
        /*
        Description: Stores a Uses(STATEMENT_NAME, VAR_NAME) relationship to
                     the USES_TABLE when building the PKB.
        */

    void addUses(PROC_NAME p, VAR_NAME v);
        /*
        Description: Stores a Uses(PROC_NAME, VAR_NAME) relationship to
                     the USES_TABLE when building the PKB.
        */

    void addModifies(STMT_NUM s, VAR_NAME v);
        /*
        Description: Stores a Modifies(STMT_NUM, VAR_NAME) relationship to
                     the MODIFIES_TABLE when building the PKB.
        */

    void addModifies(PROC_NAME p, VAR_NAME v);
        /*
        Description: Stores a Modifies(PROC_NAME, VAR_NAME) relationship to
                     the MODIFIES_TABLE when building the PKB.
        */

    void setProgramNode(PROGRAM_NODE_PTR program_node_ptr);
        /*
        Description: Stores the root/program node pointer into the PKB.
        */

    PKB build();
        /*
        Description: We create an immutable PKB containing all the design entities,
                     relationship information and AST information provided.
        */

private:
    friend class PKB;

    PROGRAM_NODE_PTR program_node_ptr;

    ASSIGN_TABLE assign_table_;
    CONSTANT_TABLE constant_table_;
    IF_TABLE if_table_;
    PRINT_TABLE print_table_;
    PROC_TABLE proc_table_;
    READ_TABLE read_table_;
    STMT_LIST_TABLE stmt_list_table_;
    STMT_TABLE stmt_table_;
    VAR_TABLE var_table_;
    WHILE_TABLE while_table_;

    FOLLOWS_TABLE follows_table_;
    PARENT_TABLE parent_table_;
    USES_TABLE uses_table_;
    MODIFIES_TABLE modifies_table_;
};

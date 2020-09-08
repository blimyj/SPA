#pragma once

class PKBBuilder {
/* Overview: A builder to aid in the construction of the PKB */

public:
    /*==== Design Entities ====*/
    INDEX addStatement(STMT_NUM s);
        /*
        Description: Adds a STMT_NUM to the STATEMENT_TABLE when building the PKB.
                     Returns the INDEX of the STMT_NUM in the STATEMENT_TABLE.
        */

    INDEX addRead(STMT_NUM s);
        /*
        Description: Adds a STMT_NUM to the READ_TABLE when building the PKB.
                     Returns the INDEX of the STMT_NUM in the READ_TABLE.
        */

    INDEX addPrint(STMT_NUM s);
        /*
        Description: Adds a STMT_NUM to the PRINT_TABLE when building the PKB.
                     Returns the INDEX of the STMT_NUM in the PRINT_TABLE.
        */

    INDEX addWhile(STMT_NUM s);
        /*
        Description: Adds a STMT_NUM to the WHILE_TABLE when building the PKB.
                     Returns the INDEX of the STMT_NUM in the WHILE_TABLE.
        */

    INDEX addIf(STMT_NUM s);
        /*
        Description: Adds a STMT_NUM to the IF_TABLE when building the PKB.
                     Returns the INDEX of the STMT_NUM in the IF_TABLE.
        */

    INDEX addAssign(STMT_NUM s);
        /*
        Description: Adds a STMT_NUM to the ASSIGN_TABLE when building the PKB.
                     Returns the INDEX of the STMT_NUM in the ASSIGN_TABLE.
        */

    INDEX addConstant(CONSTANT_NAME c);
        /*
        Description: Adds a CONSTANT_NAME to the CONSTANT_TABLE when building the PKB.
                     Returns the INDEX of the CONSTANT_NAME in the CONSTANT_TABLE.
        */

    INDEX addVariable(VAR_NAME v);
        /*
        Description: Adds a VAR_NAME to the VARIABLE_TABLE when building the PKB.
                     Returns the INDEX of the VAR_NAME in the VARIABLE_TABLE.
        */

    INDEX addProcedure(PROC_NAME p);
        /*
        Description: Adds a PROC_NAME to the PROCEDURE_TABLE when building the PKB.
                     Returns the INDEX of the PROC_NAME in the PROCEDURE_TABLE.
        */

    /*==== Relationships ====*/
    VOID addFollows(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Stores a Follows(STMT_NUM, STMT_NUM) relationship to
                     the FOLLOWS_TABLE when building the PKB.
        */
    VOID addParent(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Stores a Parent(STMT_NUM, STMT_NUM) relationship to
                     the PARENT_TABLE when building the PKB.
        */
    VOID addUses(STMT_NUM s, VAR_NAME v);
        /*
        Description: Stores a Uses(STATEMENT_NAME, VAR_NAME) relationship to
                     the USES_TABLE when building the PKB.
        */

    VOID addUses(PROC_NAME p, VAR_NAME v);
        /*
        Description: Stores a Uses(PROC_NAME, VAR_NAME) relationship to
                     the USES_TABLE when building the PKB.
        */

    VOID addModifies(STMT_NUM s, VAR_NAME v);
        /*
        Description: Stores a Modifies(STMT_NUM, VAR_NAME) relationship to
                     the MODIFIES_TABLE when building the PKB.
        */

    VOID addModifies(PROC_NAME p, VAR_NAME v);
        /*
        Description: Stores a Modifies(PROC_NAME, VAR_NAME) relationship to
                     the MODIFIES_TABLE when building the PKB.
        */

    VOID setProgramAST(PROGRAM_AST_NODE node);
        /*
        Description: Stores the source program's AST into the PKB when building the PKB.
        */

    PKB build();
        /*
        Description: We create an immutable PKB containing all the design entities,
                     relationship information and AST information provided.
        */
};

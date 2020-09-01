#pragma once

class PKBBuilder {
/* Overview: A builder to aid in the construction of the PKB */

public:
    /*==== Design Entities ====*/
    INDEX addStatement(STATEMENT_NUMBER s);
        /*
        Description: Adds a STATEMENT_NUMBER to the STATEMENT_TABLE when building the PKB.
                     Returns the INDEX of the STATEMENT_NUMBER in the STATEMENT_TABLE.
        */

    INDEX addRead(STATEMENT_NUMBER s);
        /*
        Description: Adds a STATEMENT_NUMBER to the READ_TABLE when building the PKB.
                     Returns the INDEX of the STATEMENT_NUMBER in the READ_TABLE.
        */

    INDEX addPrint(STATEMENT_NUMBER s);
        /*
        Description: Adds a STATEMENT_NUMBER to the PRINT_TABLE when building the PKB.
                     Returns the INDEX of the STATEMENT_NUMBER in the PRINT_TABLE.
        */

    INDEX addWhile(STATEMENT_NUMBER s);
        /*
        Description: Adds a STATEMENT_NUMBER to the WHILE_TABLE when building the PKB.
                     Returns the INDEX of the STATEMENT_NUMBER in the WHILE_TABLE.
        */ 

    INDEX addIf(STATEMENT_NUMBER s);
        /*
        Description: Adds a STATEMENT_NUMBER to the IF_TABLE when building the PKB.
                     Returns the INDEX of the STATEMENT_NUMBER in the IF_TABLE.
        */

    INDEX addAssign(STATEMENT_NUMBER s);
        /*
        Description: Adds a STATEMENT_NUMBER to the ASSIGN_TABLE when building the PKB.
                     Returns the INDEX of the STATEMENT_NUMBER in the ASSIGN_TABLE.
        */

    INDEX addConstant(CONSTANT_NAME c);
        /*
        Description: Adds a CONSTANT_NAME to the CONSTANT_TABLE when building the PKB.
                     Returns the INDEX of the CONSTANT_NAME in the CONSTANT_TABLE.
        */

    INDEX addVariable(VARIABLE_NAME v);
        /*
        Description: Adds a VARIABLE_NAME to the VARIABLE_TABLE when building the PKB.
                     Returns the INDEX of the VARIABLE_NAME in the VARIABLE_TABLE.
        */

    INDEX addProcedure(PROCEDURE_NAME p);
        /*
        Description: Adds a PROCEDURE_NAME to the PROCEDURE_TABLE when building the PKB.
                     Returns the INDEX of the PROCEDURE_NAME in the PROCEDURE_TABLE.
        */

    /*==== Relationships ====*/
    VOID addFollows(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
        /*
        Description: Stores a Follows(STATEMENT_NUMBER, STATEMENT_NUMBER) relationship to
                     the FOLLOWS_TABLE when building the PKB.
        */
    VOID addParent(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
        /*
        Description: Stores a Parent(STATEMENT_NUMBER, STATEMENT_NUMBER) relationship to
                     the PARENT_TABLE when building the PKB.
        */
    VOID addUses(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Stores a Uses(STATEMENT_NAME, VARIABLE_NAME) relationship to
                     the USES_TABLE when building the PKB.
        */

    VOID addUses(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Stores a Uses(PROCEDURE_NAME, VARIABLE_NAME) relationship to
                     the USES_TABLE when building the PKB.
        */

    VOID addModifies(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Stores a Modifies(STATEMENT_NUMBER, VARIABLE_NAME) relationship to
                     the MODIFIES_TABLE when building the PKB.
        */

    VOID addModifies(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Stores a Modifies(PROCEDURE_NAME, VARIABLE_NAME) relationship to
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

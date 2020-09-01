#pragma once

class PKB {
/* Overview: The PKB that contains design entities and relationships of a given SIMPLE source code */

public:
    /*==== Constructor ====*/
    PKB(PKB_BUILDER builder);

    /*==== Design Entities ====*/
    STATEMENT_NUMBER_LIST getStatements();
        /*
        Description: Returns the STATEMENT_NUMBER_LIST stored in STATEMENT_TABLE.
                     If there are no elements in the collection, returns an empty
                     STATEMENT_NUMBER_LIST.
        */

    STATEMENT_NUMBER_LIST getReads();
        /*
        Description: Returns the STATEMENT_NUMBER_LIST stored in READ_TABLE.
                     If there are no elements in the collection, returns an empty
                     STATEMENT_NUMBER_LIST.
        */

    STATEMENT_NUMBER_LIST getPrints();
        /*
        Description: Returns the STATEMENT_NUMBER_LIST stored in PRINT_TABLE.
                     If there are no elements in the collection, returns an empty
                     STATEMENT_NUMBER_LIST.
        */
    
    STATEMENT_NUMBER_LIST getWhiles();
        /*
        Description: Returns the STATEMENT_NUMBER_LIST stored in WHILE_TABLE.
                     If there are no elements in the collection, returns an empty
                     STATEMENT_NUMBER_LIST.
        */
    
    STATEMENT_NUMBER_LIST getIfs();
        /*
        Description: Returns the STATEMENT_NUMBER_LIST stored in IF_TABLE.
                     If there are no elements in the collection, returns an empty
                     STATEMENT_NUMBER_LIST.
        */
    
    STATEMENT_NUMBER_LIST getAssigns();
        /*
        Description: Returns the STATEMENT_NUMBER_LIST stored in ASSIGN_TABLE.
                     If there are no elements in the collection, returns an empty
                     STATEMENT_NUMBER_LIST.
        */
    
    CONSTANT_NAME_LIST getConstants();
        /*
        Description: Returns the CONSTANT_NAME_LIST stored in CONSTANT_TABLE.
                     If there are no elements in the collection, returns an empty
                     CONSTANT_NAME_LIST.
        */

    VARIABLE_NAME_LIST getVariables();
        /*
        Description: Returns the VARIABLE_NAME_LIST stored in VARIABLE_TABLE.
                     If there are no elements in the collection, returns an empty
                     VARIABLE_NAME_LIST.
        */
    
    PROCEDURE_NAME_LIST getProcedures();
        /*
        Description: Returns the PROCEDURE_NAME_LIST stored in PROCEDURE_TABLE.
                     If there are no elements in the collection, returns an empty
                     PROCEDURE_NAME_LIST.
        */

    /*==== Relationships ====*/
    BOOLEAN isFollows(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Follows(STATEMENT_NUMBER, STATEMENT_NUMBER) holds
        */

    BOOLEAN isParent(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Parent(STATEMENT_NUMBER, STATEMENT_NUMBER) holds
        */

    BOOLEAN isUses(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Uses(STATEMENT_NUMBER, VARIABLE_NAME) holds
        */

    BOOLEAN isUses(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Uses(PROCEDURE_NAME, VARIABLE_NAME) holds
        */

    BOOLEAN isModifies(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Modifies(STATEMENT_NUMBER, VARIABLE_NAME) holds
        */

    BOOLEAN isModifies(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not
                     Modifies(PROCEDURE_NAME, VARIABLE_NAME) holds
        */

    /*==== AST ====*/
    PROGRAM_AST_NODE getProgramAST();
        /*
        Description: Returns the source program's AST.
        */
};

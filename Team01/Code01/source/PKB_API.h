#ifndef AST_API_H
#define AST_API_H

class PKBBuilder {
/* Overview: A builder to aid in the construction of the PKB */

public:
    VOID addStatement(STATEMENT_NODE s);
        /*
        Description:
            Normal: Adds a STATEMENT_NODE when building the PKB
            Abnormal: If 's' cannot be casted to STATEMENT_NODE, throw an exception
        */

    VOID addRead(READ_NODE r);
        /*
        Description:
            Normal: Adds a READ_NODE when building the PKB
            Abnormal: If 'r' cannot be casted to READ_NODE, throw an exception
        */

    VOID addPrint(PRINT_NODE p);
        /*
        Description:
            Normal: Adds a PRINT_NODE when building the PKB
            Abnormal: If 'p' cannot be casted to PRINT_NODE, throw an exception
        */

    VOID addCall(CALL_NODE c);
        /*
        Description:
            Normal: Adds a CALL_NODE when building the PKB
            Abnormal: If 'c' cannot be casted to CALL_NODE, throw an exception
        */

    VOID addWhile(WHILE_NODE w);
        /*
        Description:
            Normal: Adds a WHILE_NODE when building the PKB
            Abnormal: If 'w' cannot be casted to WHILE_NODE, throw an exception
        */

    VOID addIf(IF_NODE i);
        /*
        Description:
            Normal: Adds a IF_NODE when building the PKB
            Abnormal: If 'i' cannot be casted to IF_NODE, throw an exception
        */

    VOID addAssign(ASSIGN_NODE a);
        /*
        Description:
            Normal: Adds a ASSIGN_NODE when building the PKB
            Abnormal: If 'a' cannot be casted to ASSIGN_NODE, throw an exception
        */

    VOID addConstant(CONSTANT_NODE c);
        /*
        Description:
            Normal: Adds a CONSTANT_NODE when building the PKB
            Abnormal: If 'c' cannot be casted to CONSTANT_NODE, throw an exception
        */

    INDEX addVariable(VARIABLE_NODE v);
        /*
        Description:
            Normal: Adds a VARIABLE_NODE to the VARIABLE_TABLE when building the PKB.
                    Returns the INDEX of the VARIABLE_NODE in the VARIABLE_TABLE.
            Abnormal: If 'v' cannot be casted to VARIABLE_NODE, throw an exception
        */

    INDEX addProcedure(PROCEDURE_NODE p);
        /*
        Description:
            Normal: Adds a PROCEDURE_NODE to the PROCEDURE_TABLE when building the PKB.
                    Returns the INDEX of the PROCEDURE_NODE in the PROCEDURE_TABLE.
            Abnormal: If 'p' cannot be casted to PROCEDURE_NODE, throw an exception
        */

    PKB build();
        /*
        Requires: At least one PROCEDURE_NODE and one STATEMENT_NODE must be added
        Description:
            Normal: With the design entities obtained from the given methods, we derive 
                    the relationships and create a new PKB.
            Abnormal: If there isn't a PROCEDURE_NODE or STATEMENT_NODE added, throw an exception
        */
};

class PKB {
/* Overview: The PKB that contains design entities and relationships of a given SIMPLE source code */

public:
    /* Design Entities */
    STATEMENT_NODE_LIST getStatements();
    /*
    Description:
        Normal: Returns the collection of STATEMENT_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty STATEMENT_NODE_LIST.
    */

    READ_NODE_LIST getReads();
    /*
    Description:
        Normal: Returns the collection of READ_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty READ_NODE_LIST.
    */

    PRINT_NODE_LIST getPrints();
    /*
    Description:
        Normal: Returns the collection of PRINT_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty PRINT_NODE_LIST.
    */

    CALL_NODE_LIST getCalls();
    /*
    Description:
        Normal: Returns the collection of CALL_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty CALL_NODE_LIST.
    */
    
    WHILE_NODE_LIST getWhiles();
    /*
    Description:
        Normal: Returns the collection of WHILE_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty WHILE_NODE_LIST.
    */
    
    IF_NODE_LIST getIfs();
    /*
    Description:
        Normal: Returns the collection of IF_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty IF_NODE_LIST.
    */
    
    ASSIGN_NODE_LIST getAssigns();
    /*
    Description:
        Normal: Returns the collection of ASSIGN_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty ASSIGN_NODE_LIST.
    */
    
    VARIABLE_NODE_LIST getVariables();
    /*
    Description:
        Normal: Returns the collection of VARIABLE_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty VARIABLE_NODE_LIST.
    */
    
    CONSTANT_NODE_LIST getConstants();
    /*
    Description:
        Normal: Returns the collection of CONSTANT_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty CONSTANT_NODE_LIST.
    */
    
    PROCEDURE_NODE_LIST getProcedures();
    /*
    Description:
        Normal: Returns the collection of PROCEDURE_NODE stored in the PKB.
                If there are no elements in the collection, returns an empty PROCEDURE_NODE_LIST.
    */

    /* Relationships */
    BOOLEAN isFollows(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
    /*
    Description:
        Normal: Returns TRUE if s1 follows s2, and FALSE otherwise
    */

    BOOLEAN isFollowsT(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
    /*
    Description:
        Normal: Returns TRUE if s1 follows a set of STATEMENT_NUMBER that follows s2,
                and FALSE otherwise
    */

    BOOLEAN isParent(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
    /*
    Description:
        Normal: Returns TRUE if s1 is a parent of s2, and FALSE otherwise
    */

    BOOLEAN isParentT(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
    /*
    Description:
        Normal: Returns TRUE if s1 is a parent of a set of STATEMENT_NUMBER that are parents of s2,
                and FALSE otherwise
    */

    BOOLEAN isUses(STATEMENT_NUMBER s, VARIABLE_NAME v);
    /*
    Description:
        Normal: Returns TRUE if statement s uses the variable v, and FALSE otherwise
    */

    BOOLEAN isUses(PROCEDURE_NAME p, VARIABLE_NAME v);
    /*
    Description:
        Normal: Returns TRUE if procedure p uses the variable v, and FALSE otherwise
    */

    BOOLEAN isModifies(STATEMENT_NUMBER s, VARIABLE_NAME v);
    /*
    Description:
        Normal: Returns TRUE if statement s modfies the variable v, and FALSE otherwise
    */

    BOOLEAN isUses(PROCEDURE_NAME p, VARIABLE_NAME v);
    /*
    Description:
        Normal: Returns TRUE if procedure p modfies the variable v, and FALSE otherwise
    */
};

class VariableTable {
/* Overview: This is a data structure that maps INDEX to VARIABLE_NODE */

public:
    INDEX addVariable(VARIABLE_NODE v);
    /*
    Description:
        Normal: Stores a VARIABLE_NODE in this table.
                Returns the INDEX of the VARIABLE_NODE in this table.
        Abnormal: If 'v' cannot be casted to VARIABLE_NODE, throw an exception.
    */

    VARIABLE_NODE_LIST getVariables();
    /*
    Description:
        Normal: Return a list of VARIABLE_NODE from this table.
                If there are no elements in the collection, returns an empty VARIABLE_NODE_LIST.
    */

   VARIABLE_NODE getVariable(INDEX i);
    /*
    Description:
        Normal: Return the VARIABLE_NODE at INDEX 'i' in this table.
        Abnormal: If INDEX 'i' is out of range, throw an exception
    */
};

class ProcedureTable {
/* Overview: This is a data structure that maps INDEX to PROCEDURE_NODE */

public:
    INDEX addProcedure(PROCEDURE_NODE p);
    /*
    Description:
        Normal: Stores a PROCEDURE_NODE in this table.
                Returns the INDEX of the PROCEDURE_NODE in this table.
        Abnormal: If 'p' cannot be casted to PROCEDURE_NODE, throw an exception.
    */

    PROCEDURE_NODE_LIST getProcedures();
    /*
    Description:
        Normal: Return a list of PROCEDURE_NODE from this table.
                If there are no elements in the collection, returns an empty PROCEDURE_NODE_LIST.
    */

   PROCEDURE_NODE getProcedure(INDEX i);
    /*
    Description:
        Normal: Returns the PROCEDURE_NODE at INDEX 'i' in this table.
        Abnormal: If INDEX 'i' is out of range, throw an exception
    */
};

#endif

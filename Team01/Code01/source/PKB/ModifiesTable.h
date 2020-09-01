#pragma once

class ModifiesTable {
/* Overview: This is a data structure*/

public:
    VOID addModifies(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Adds to a collection that maps s to v.
        */

    VOID addModifies(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Adds to a collection that maps p to v.
        */

    BOOLEAN isModifies(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Modifies(s, v) holds.
        */

    BOOLEAN isModifies(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Modifies(p, v) holds.
        */
};

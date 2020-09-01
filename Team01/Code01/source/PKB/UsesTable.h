#pragma once

class UsesTable {
/* Overview: This is a data structure*/

public:
    VOID addUses(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Adds to a collection that maps s to v.
        */

    VOID addUses(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Adds to a collection that maps p to v.
        */

    BOOLEAN isUses(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Uses(s, v) holds.
        */

    BOOLEAN isUses(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Uses(p, v) holds.
        */
};

#pragma once

class ProcedureTable {
/* Overview: This is a data structure*/

public:
    INDEX addProcedureName(PROCEDURE_NAME s);
        /*
        Description: Returns the index of the PROCEDURE_NAME that is added to the table.
        */

    PROCEDURE_NAME_LIST getProcedureName();
        /*
        Description: Returns a collection of PROCEDURE_NAME added to this table.
        */
};

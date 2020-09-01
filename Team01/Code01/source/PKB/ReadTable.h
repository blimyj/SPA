#pragma once

class ReadTable {
/* Overview: This is a data structure*/

public:
    INDEX addStatementNumber(STATEMENT_NUMBER s);
        /*
        Description: Returns the index of the STATEMENT_NUMBER that is added to the table.
        */

    STATEMENT_NUMBER_LIST getStatementNumberList();
        /*
        Description: Returns a collection of STATEMENT_NUMBER added to this table.
        */
};

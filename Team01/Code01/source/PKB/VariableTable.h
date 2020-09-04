#pragma once

class VariableTable {
/* Overview: This is a data structure*/

public:
    INDEX addVariableName(VARIABLE_NAME v);
        /*
        Description: Returns the index of the VARIABLE_NAME that is added to the table.
        */

    VARIABLE_NAME_LIST getVariableNameList();
        /*
        Description: Returns a collection of VARIALBE_NAME added to this table.
        */

private:
    TABLE table_;
};

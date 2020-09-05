#include <iostream>
#include <vector>
#include "ProcedureTable.h"

typedef int INDEX;
typedef std::string PROCEDURE_NAME;
typedef std::vector<PROCEDURE_NAME> TABLE;
typedef std::vector<PROCEDURE_NAME> PROCEDURE_NAME_LIST;

INDEX ProcedureTable::addProcedureName(PROCEDURE_NAME p) {
    INDEX index = table_.size();
    table_.push_back(p);
    return index;
}

STATEMENT_NUMBER_LIST ProcedureTable::getProcedureNameList() {
    PROCEDURE_NAME_LIST copy;
    for (PROCEDURE_NAME p : table_) {
        copy.push_back(p);
    }
    return copy;
}

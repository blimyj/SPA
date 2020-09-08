#include "ModifiesTable.h"

VOID ModifiesTable::addModifies(STATEMENT_NUMBER s, VARIABLE_NAME v) {
    statement_table_.insert({ s, v });
}

VOID ModifiesTable::addModifies(PROCEDURE_NAME p, VARIABLE_NAME v) {
    procedure_table_.insert({ p, v });
}

BOOLEAN ModifiesTable::isModifies(STATEMENT_NUMBER s, VARIABLE_NAME v) {
    auto it = statement_table_.find(s);
    if (it == statement_table_.end()) {
        return false;
    }
    return it->second == v;
}

BOOLEAN ModifiesTable::isModifies(PROCEDURE_NAME p, VARIABLE_NAME v) {
    auto it = procedure_table_.find(p);
    if (it == procedure_table_.end()) {
        return false;
    }
    return it->second == v;
}

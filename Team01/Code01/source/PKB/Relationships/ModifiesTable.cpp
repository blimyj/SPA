#include "ModifiesTable.h"

VOID ModifiesTable::addModifies(STMT_NUM s, VAR_NAME v) {
    statement_table_.insert({ s, v });
}

VOID ModifiesTable::addModifies(PROC_NAME p, VAR_NAME v) {
    procedure_table_.insert({ p, v });
}

BOOLEAN ModifiesTable::isModifies(STMT_NUM s, VAR_NAME v) {
    auto it = statement_table_.find(s);
    if (it == statement_table_.end()) {
        return false;
    }
    return it->second == v;
}

BOOLEAN ModifiesTable::isModifies(PROC_NAME p, VAR_NAME v) {
    auto it = procedure_table_.find(p);
    if (it == procedure_table_.end()) {
        return false;
    }
    return it->second == v;
}

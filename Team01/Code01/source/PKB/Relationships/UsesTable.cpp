#include "UsesTable.h"

VOID UsesTable::addUses(STMT_NUM s, VAR_NAME v) {
    statement_table_.insert({ s, v });
}

VOID UsesTable::addUses(PROC_NAME p, VAR_NAME v) {
    procedure_table_.insert({ p, v });
}

BOOLEAN UsesTable::isUses(STMT_NUM s, VAR_NAME v) {
    auto it = statement_table_.find(s);
    if (it == statement_table_.end()) {
        return false;
    }
    return it->second == v;
}

BOOLEAN UsesTable::isUses(PROC_NAME p, VAR_NAME v) {
    auto it = procedure_table_.find(p);
    if (it == procedure_table_.end()) {
        return false;
    }
    return it->second == v;
}

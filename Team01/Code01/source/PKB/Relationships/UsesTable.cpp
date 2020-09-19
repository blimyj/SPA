#include "UsesTable.h"

void UsesTable::addUses(STMT_NUM s, VAR_NAME v) {
    uses_s_.insert({ s, v });
}

void UsesTable::addUses(PROC_NAME p, VAR_NAME v) {
    uses_p_.insert({ p, v });
}

BOOLEAN_TYPE UsesTable::isUses(STMT_NUM s, VAR_NAME v) {
    return uses_s_.count({ s, v }) > 0;
}

BOOLEAN_TYPE UsesTable::isUses(PROC_NAME p, VAR_NAME v) {
    return uses_p_.count({ p, v }) > 0;
}

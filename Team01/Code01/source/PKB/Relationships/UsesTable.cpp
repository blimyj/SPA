#include "UsesTable.h"

VOID UsesTable::addUses(STMT_NUM s, VAR_NAME v) {
    uses_s_.insert({ s, v });
}

VOID UsesTable::addUses(PROC_NAME p, VAR_NAME v) {
    uses_p_.insert({ p, v });
}

BOOLEAN UsesTable::isUses(STMT_NUM s, VAR_NAME v) {
    return uses_s_.count({ s, v }) > 0;
}

BOOLEAN UsesTable::isUses(PROC_NAME p, VAR_NAME v) {
    return uses_p_.count({ p, v }) > 0;
}

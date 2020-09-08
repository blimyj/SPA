#include "ParentTable.h"

VOID ParentTable::addParent(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2) {
    table_.insert({ s1, s2 });
}

BOOLEAN ParentTable::isParent(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2) {
    auto it = table_.find(s1);
    if (it == table_.end()) {
        return false;
    }
    return it->second == s2;
}

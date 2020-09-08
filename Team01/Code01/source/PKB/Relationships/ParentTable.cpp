typedef void VOID;
typedef bool BOOLEAN;
typedef std::shared_ptr<std::string> STATEMENT_NUMBER;
typedef std::unordered_map<STATEMENT_NUMBER, STATEMENT_NUMBER> TABLE;

#include <iostream>
#include <unordered_map>
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

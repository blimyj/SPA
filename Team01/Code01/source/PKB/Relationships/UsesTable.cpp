typedef void VOID;
typedef bool BOOLEAN;
typedef std::shared_ptr<std::string> STATEMENT_NUMBER;
typedef std::shared_ptr<std::string> PROCEDURE_NAME;
typedef std::shared_ptr<std::string> VARIABLE_NAME;
typedef std::unordered_map<STATEMENT_NUMBER, VARIABLE_NAME> STATEMENT_TABLE;
typedef std::unordered_map<PROCEDURE_NAME, VARIABLE_NAME> PROCEDURE_TABLE;

#include <iostream>
#include <unordered_map>
#include "UsesTable.h"

VOID UsesTable::addUses(STATEMENT_NUMBER s, VARIABLE_NAME v) {
    statement_table_.insert({ s, v });
}

VOID UsesTable::addUses(PROCEDURE_NAME p, VARIABLE_NAME v) {
    procedure_table_.insert({ p, v });
}

BOOLEAN UsesTable::isUses(STATEMENT_NUMBER s, VARIABLE_NAME v) {
    auto it = statement_table_.find(s);
    if (it == statement_table_.end()) {
        return false;
    }
    return it->second == v;
}

BOOLEAN UsesTable::isUses(PROCEDURE_NAME p, VARIABLE_NAME v) {
    auto it = procedure_table_.find(p);
    if (it == procedure_table_.end()) {
        return false;
    }
    return it->second == v;
}

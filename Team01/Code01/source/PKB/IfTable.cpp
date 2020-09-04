#include <iostream>
#include <vector>
#include "IfTable.h"

typedef int INDEX;
typedef std::string STATEMENT_NUMBER;
typedef std::vector<STATEMENT_NUMBER> STATEMENT_NUMBER_LIST;

INDEX IfTable::addStatementNumber(STATEMENT_NUMBER n) {
    INDEX index = table_.size();
    table_.push_back(n);
    return index;
}

STATEMENT_NUMBER_LIST IfTable::getStatementNumberList() {
    STATEMENT_NUMBER_LIST copy;
    for (STATEMENT_NUMBER n : table_) {
        copy.push_back(n);
    }
    return copy;
}

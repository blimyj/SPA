#include <iostream>
#include <vector>
#include "PrintTable.h"

typedef int INDEX;
typedef std::string STATEMENT_NUMBER;
typedef std::vector<STATEMENT_NUMBER> TABLE;
typedef std::vector<STATEMENT_NUMBER> STATEMENT_NUMBER_LIST;

INDEX PrintTable::addStatementNumber(STATEMENT_NUMBER s) {
    INDEX index = table_.size();
    table_.push_back(s);
    return index;
}

STATEMENT_NUMBER_LIST PrintTable::getStatementNumberList() {
    STATEMENT_NUMBER_LIST copy;
    for (STATEMENT_NUMBER s : table_) {
        copy.push_back(s);
    }
    return copy;
}

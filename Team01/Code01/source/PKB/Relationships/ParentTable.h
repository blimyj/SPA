#pragma once

#include <memory>
#include <string>
#include <unordered_map>

typedef void VOID;
typedef bool BOOLEAN;
typedef std::shared_ptr<std::string> STATEMENT_NUMBER;
typedef std::unordered_map<STATEMENT_NUMBER, STATEMENT_NUMBER> TABLE;

class ParentTable {
/* Overview: This is a data structure*/

public:
    VOID addParent(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
        /*
        Description: Adds to a collection that maps s1 to s2.
        */

    BOOLEAN isParent(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not Parent(s1, s2) holds.
        */

private:
    TABLE table_;

};

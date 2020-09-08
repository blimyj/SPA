#pragma once

#include <memory>
#include <string>
#include <unordered_map>

typedef void VOID;
typedef bool BOOLEAN;
typedef std::shared_ptr<int> STMT_NUM;
typedef std::unordered_map<STMT_NUM, STMT_NUM> PARENT_TABLE;

class ParentTable {
/* Overview: This is a data structure*/

public:
    VOID addParent(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Adds to a collection that maps s1 to s2.
        */

    BOOLEAN isParent(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not Parent(s1, s2) holds.
        */

private:
    PARENT_TABLE table_;

};

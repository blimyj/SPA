#pragma once

#include <unordered_map>
#include <unordered_set>
#include "../Hashing.h"

typedef bool BOOLEAN_TYPE;
typedef int STMT_NUM;

class ParentTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    void addParent(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Stores the relationship Parent(s1, s2) in the table.
        */

    BOOLEAN_TYPE isParent(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Returns a BOOLEAN_TYPE indicating whether or not Parent(s1, s2) holds.
        */

    BOOLEAN_TYPE isParentTransitive(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Returns a BOOLEAN_TYPE indicating whether or not Parent*(s1, s2) holds.
        */

    std::unordered_map<STMT_NUM, std::vector<STMT_NUM>> statements_;
    std::unordered_set<std::pair<STMT_NUM, STMT_NUM>> parent_;
    std::unordered_map<std::pair<STMT_NUM, STMT_NUM>, BOOLEAN_TYPE> parent_transitive_;

};

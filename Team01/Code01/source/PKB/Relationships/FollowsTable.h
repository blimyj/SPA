#pragma once

#include <unordered_map>
#include <unordered_set>
#include "../Hashing.h"

typedef void VOID;
typedef bool BOOLEAN;
typedef int STMT_NUM;

class FollowsTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    VOID addFollows(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Stores the relationship Follows(s1, s2) in the table.
        */

    BOOLEAN isFollows(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not Follows(s1, s2) holds.
        */

    BOOLEAN isFollowsTransitive(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not Follows*(s1, s2) holds.
        */

    std::unordered_map<STMT_NUM, STMT_NUM> statements_;
    std::unordered_set<std::pair<STMT_NUM, STMT_NUM>> follows_;
    std::unordered_map<std::pair<STMT_NUM, STMT_NUM>, BOOLEAN> follows_transitive_;

};

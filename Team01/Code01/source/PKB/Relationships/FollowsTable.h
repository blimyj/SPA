#pragma once

#include <memory>
#include <string>
#include <unordered_map>

typedef void VOID;
typedef bool BOOLEAN;
typedef int STMT_NUM;

class FollowsTable {
/* Overview: This is a data structure*/

public:
    VOID addFollows(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Adds to a collection that maps s1 to s2.
        */

    BOOLEAN isFollows(STMT_NUM s1, STMT_NUM s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not Follows(s1, s2) holds.
        */

private:
    std::unordered_map<STMT_NUM, STMT_NUM> table_;

};

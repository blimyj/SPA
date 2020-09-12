#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

typedef void VOID;
typedef bool BOOLEAN;
typedef int STMT_NUM;

class FollowsTable {
/* Overview: This is a data structure*/

struct HASH {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

private:
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

    VOID calculateTransitive();
        /*
        Description: Calculates transitive relationships in the table.
        */

    friend class PKB;

    std::unordered_map<STMT_NUM, STMT_NUM> statement_follows_;
    std::unordered_set<std::pair<STMT_NUM, STMT_NUM>, HASH> follows_;
    std::unordered_set<std::pair<STMT_NUM, STMT_NUM>, HASH> follows_transitive_;

};

#include "FollowsTable.h"

VOID FollowsTable::addFollows(STMT_NUM s1, STMT_NUM s2) {
    table_.insert({ s1, s2 });
}

BOOLEAN FollowsTable::isFollows(STMT_NUM s1, STMT_NUM s2) {
    auto it = table_.find(s1);
    if (it == table_.end()) {
        return false;
    }
    return it->second == s2;
}

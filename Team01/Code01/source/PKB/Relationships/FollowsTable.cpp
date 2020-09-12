#include "FollowsTable.h"

VOID FollowsTable::addFollows(STMT_NUM_PTR s1, STMT_NUM_PTR s2) {
    table_.insert({ s1, s2 });
}

BOOLEAN FollowsTable::isFollows(STMT_NUM_PTR s1, STMT_NUM_PTR s2) {
    auto it = table_.find(s1);
    if (it == table_.end()) {
        return false;
    }
    return it->second == s2;
}

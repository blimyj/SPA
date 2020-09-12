#include <algorithm>
#include "FollowsTable.h"

VOID FollowsTable::addFollows(STMT_NUM s1, STMT_NUM s2) {
    statements_[s1] = s2;
    follows_.insert({ s1, s2 });
    follows_transitive_.insert({ { s1, s2 }, true });
}

BOOLEAN FollowsTable::isFollows(STMT_NUM s1, STMT_NUM s2) {
    // Check if Follows(s1, s2) exists
    return follows_.count({ s1, s2 }) > 0;
}

BOOLEAN FollowsTable::isFollowsTransitive(STMT_NUM s1, STMT_NUM s2) {
    // Check if Follows*(s1, s2) exists
    if (follows_transitive_.count({ s1, s2 }) > 0) {
        return true;
    }

    // Check if s1 has a follower
    auto it = statements_.find(s1);
    if (it == statements_.end()) {
        return false;
    }

    // Check if follower is transitive
    // Memoize transitive relationships :)
    if (isFollowsTransitive(it->second, s2)) {
        follows_transitive_.insert({ { s1, s2 }, true });
        return true;
    }
    follows_transitive_.insert({ { s1, s2 }, false });
    return false;
}

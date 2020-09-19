#include <algorithm>
#include "FollowsTable.h"

void FollowsTable::addFollows(STMT_NUM s1, STMT_NUM s2) {
    statements_[s1] = s2;
    follows_.insert({ s1, s2 });
    follows_transitive_.insert({ { s1, s2 }, true });
}

BOOLEAN_TYPE FollowsTable::isFollows(STMT_NUM s1, STMT_NUM s2) {
    // Check if Follows(s1, s2) exists
    return follows_.count({ s1, s2 }) > 0;
}

BOOLEAN_TYPE FollowsTable::isFollowsTransitive(STMT_NUM s1, STMT_NUM s2) {
    // Check if Follows*(s1, s2) exists, and return it's value
    auto it1 = follows_transitive_.find({ s1, s2 });
    if (it1 != follows_transitive_.end()) {
        return it1->second;
    }

    // Check if s1 has a follower
    auto it2 = statements_.find(s1);
    if (it2 == statements_.end()) {
        return false;
    }

    // Check if follower is transitive
    // Memoize transitive relationships :)
    if (isFollowsTransitive(it2->second, s2)) {
        follows_transitive_.insert({ { s1, s2 }, true });
        return true;
    }
    follows_transitive_.insert({ { s1, s2 }, false });
    return false;
}

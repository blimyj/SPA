#include "ParentTable.h"

void ParentTable::addParent(STMT_NUM s1, STMT_NUM s2) {
    statements_[s1].push_back(s2);
    parent_.insert({ s1, s2 });
    parent_transitive_.insert({ { s1, s2 }, true });
}

BOOLEAN_TYPE ParentTable::isParent(STMT_NUM s1, STMT_NUM s2) {
    // Check if Parent(s1, s2) exists
    return parent_.count({ s1, s2 }) > 0;
}

BOOLEAN_TYPE ParentTable::isParentTransitive(STMT_NUM s1, STMT_NUM s2) {
    // Check if Parent*(s1, s2) exists, and return it's value
    auto it1 = parent_transitive_.find({ s1, s2 });
    if (it1 != parent_transitive_.end()) {
        return it1->second;
    }

    // Check if s1 is a container
    auto it2 = statements_.find(s1);
    if (it2 == statements_.end()) {
        return false;
    }

    // Iterate children of s1 and check if they are transitive
    // Memoize transitive relationships :)
    for (STMT_NUM c : it2->second) {
        if (isParentTransitive(c, s2)) {
            parent_transitive_.insert({ { s1, s2 }, true });
            return true;
        }
    }
    parent_transitive_.insert({ { s1, s2 }, false });
    return false;
}

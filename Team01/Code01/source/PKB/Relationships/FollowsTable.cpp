#include "FollowsTable.h"

VOID FollowsTable::addFollows(STMT_NUM s1, STMT_NUM s2) {
    statement_follows_[s1] = s2;
    follows_.insert({ s1, s2 });
    follows_transitive_.insert({ s1, s2 });
}

BOOLEAN FollowsTable::isFollows(STMT_NUM s1, STMT_NUM s2) {
    // Check if Follows(s1, s2) exists
    auto it = follows_.find({ s1, s2 });
    return it != follows_.end();
}

BOOLEAN FollowsTable::isFollowsTransitive(STMT_NUM s1, STMT_NUM s2) {
    // Check if Follows*(s1, s2) exists
    auto it = follows_transitive_.find({ s1, s2 });
    return it != follows_.end();

    // Memoize transitive relationships
    std::vector<STMT_NUM> statements;
    statements.push_back(s1);
    STMT_NUM curr = s1;
    while (curr == s2) {
        auto it = statement_follows_.find(curr);
        if (it == statement_follows_.end()) {
            return false;
        }
        STMT_NUM next = it->second;
        for (STMT_NUM s : statements) {
            follows_transitive_.insert({ s, next });
        }
        statements.push_back(next);
        curr = next;
    }
    return true;
}

VOID FollowsTable::calculateTransitive() {
    // Memoize transitive relationships
    for (std::pair<STMT_NUM, STMT_NUM> f : follows_) {
        std::vector<STMT_NUM> statements;
        statements.push_back(f.first);
        STMT_NUM curr = f.first;
        while (curr == f.second) {
            auto it = statement_follows_.find(curr);
            if (it == statement_follows_.end()) {
                break;
            }
            STMT_NUM next = it->second;
            for (STMT_NUM s : statements) {
                follows_transitive_.insert({ s, next });
            }
            statements.push_back(next);
            curr = next;
        }
    }
}
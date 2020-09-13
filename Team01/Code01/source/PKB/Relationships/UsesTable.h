#pragma once

#include <string>
#include <unordered_set>
#include "../Hashing.h"

typedef void VOID;
typedef bool BOOLEAN;
typedef int STMT_NUM;
typedef std::string PROC_NAME;
typedef std::string VAR_NAME;

class UsesTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    VOID addUses(STMT_NUM s, VAR_NAME v);
        /*
        Description: Adds to a collection that maps s to v.
        */

    VOID addUses(PROC_NAME p, VAR_NAME v);
        /*
        Description: Adds to a collection that maps p to v.
        */

    BOOLEAN isUses(STMT_NUM s, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Uses(s, v) holds.
        */

    BOOLEAN isUses(PROC_NAME p, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Uses(p, v) holds.
        */

    std::unordered_set<std::pair<STMT_NUM, VAR_NAME>> uses_s_;
    std::unordered_set<std::pair<PROC_NAME, VAR_NAME>> uses_p_;

};

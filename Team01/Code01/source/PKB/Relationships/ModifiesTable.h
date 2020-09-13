#pragma once

#include <string>
#include <unordered_set>
#include "../Hashing.h"

typedef void VOID;
typedef bool BOOLEAN;
typedef int STMT_NUM;
typedef std::string PROC_NAME;
typedef std::string VAR_NAME;

class ModifiesTable {
/* Overview: This is a data structure*/

private:
    friend class PKB;
    friend class PKBBuilder;

    VOID addModifies(STMT_NUM s, VAR_NAME v);
        /*
        Description: Adds to a collection that maps s to v.
        */

    VOID addModifies(PROC_NAME p, VAR_NAME v);
        /*
        Description: Adds to a collection that maps p to v.
        */

    BOOLEAN isModifies(STMT_NUM s, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Modifies(s, v) holds.
        */

    BOOLEAN isModifies(PROC_NAME p, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Modifies(p, v) holds.
        */

    std::unordered_set<std::pair<STMT_NUM, VAR_NAME>> modifies_s_;
    std::unordered_set<std::pair<PROC_NAME, VAR_NAME>> modifies_p_;

};

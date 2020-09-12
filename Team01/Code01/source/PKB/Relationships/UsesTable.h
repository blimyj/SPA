#pragma once

#include <memory>
#include <string>
#include <unordered_map>

typedef void VOID;
typedef bool BOOLEAN;
typedef std::shared_ptr<int> STMT_NUM_PTR;
typedef std::shared_ptr<std::string> PROC_NAME;
typedef std::shared_ptr<std::string> VAR_NAME;

class UsesTable {
/* Overview: This is a data structure*/

public:
    VOID addUses(STMT_NUM_PTR s, VAR_NAME v);
        /*
        Description: Adds to a collection that maps s to v.
        */

    VOID addUses(PROC_NAME p, VAR_NAME v);
        /*
        Description: Adds to a collection that maps p to v.
        */

    BOOLEAN isUses(STMT_NUM_PTR s, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Uses(s, v) holds.
        */

    BOOLEAN isUses(PROC_NAME p, VAR_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Uses(p, v) holds.
        */

private:
    std::unordered_map<STMT_NUM_PTR, VAR_NAME> statement_table_;
    std::unordered_map<PROC_NAME, VAR_NAME> procedure_table_;

};

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

typedef void VOID;
typedef bool BOOLEAN;
typedef std::shared_ptr<int> STMT_NUM;
typedef std::shared_ptr<std::string> PROC_NAME;
typedef std::shared_ptr<std::string> VAR_NAME;

class ModifiesTable {
/* Overview: This is a data structure*/

public:
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

private:
    std::unordered_map<STMT_NUM, VAR_NAME> statement_table_;
    std::unordered_map<PROC_NAME, VAR_NAME> procedure_table_;

};

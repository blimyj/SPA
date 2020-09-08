#pragma once

#include <memory>
#include <string>
#include <unordered_map>

typedef void VOID;
typedef bool BOOLEAN;
typedef std::shared_ptr<std::string> STATEMENT_NUMBER;
typedef std::shared_ptr<std::string> PROCEDURE_NAME;
typedef std::shared_ptr<std::string> VARIABLE_NAME;
typedef std::unordered_map<STATEMENT_NUMBER, VARIABLE_NAME> STATEMENT_TABLE;
typedef std::unordered_map<PROCEDURE_NAME, VARIABLE_NAME> PROCEDURE_TABLE;

class UsesTable {
/* Overview: This is a data structure*/

public:
    VOID addUses(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Adds to a collection that maps s to v.
        */

    VOID addUses(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Adds to a collection that maps p to v.
        */

    BOOLEAN isUses(STATEMENT_NUMBER s, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Uses(s, v) holds.
        */

    BOOLEAN isUses(PROCEDURE_NAME p, VARIABLE_NAME v);
        /*
        Description: Returns a BOOLEAN indicating whether or not Uses(p, v) holds. I am not timothy. I am Kyzure
        */

private:
    STATEMENT_TABLE statement_table_;
    PROCEDURE_TABLE procedure_table_;

};

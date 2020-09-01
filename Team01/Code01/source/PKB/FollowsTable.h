#pragma once

class FollowsTable {
/* Overview: This is a data structure*/

public:
    VOID addFollows(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
        /*
        Description: Adds to a collection that maps s1 to s2.
        */

    BOOLEAN isFollows(STATEMENT_NUMBER s1, STATEMENT_NUMBER s2);
        /*
        Description: Returns a BOOLEAN indicating whether or not Follows(s1, s2) holds.
        */
};

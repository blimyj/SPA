#ifndef QUERY_API_H
#define QUERY_API_H

class QueryProcessor {
	/* Overview: Oversees and drives the pre-processor and evaluator*/

public:
	QUERY_RESULT processQuery(QUERY q);
	/*
		Description:
		  Normal: Returns the QUERY_RESULT
		  Abnormal: If 'q' is not a valid query, throw an exception
		*/
};

class QueryPreProcessor {
	/* Overview: Pre-processes queries into a suitable data structure for the evaluator */

public:
	PROCESSED_SYNONYMS preProcessSynonyms(QUERY q);
	/*
		Description:
		  Normal: Returns a PROCESSED_SYNONYMS
		  Abnormal: If 'q' is not a valid query, throw an exception
		*/

	PROCESSED_CLAUSES preProcessClauses(QUERY q);
	/*
		Description:
		  Normal: Returns a PROCESSED_CLAUSES
		  Abnormal: If 'q' is not a valid query, throw an exception
		*/
};

class QueryEvaluator {
	/* Overview: Evaluates pre-processed queries and returns the result */

public:
	QUERY_RESULT evaluateQuery(PROCESSED_SYNONYMS s, PROCESSED_CLAUSES c);
	/*
		Requires: A query in the form of PROCESSED_SYNONYMS and PROCESSED_CLAUSES
		Description:
		  Normal: Returns the QUERY_RESULT
		  Abnormal: If 's' and 'c' is not a valid processed query, throw an exception
		*/
};

class QueryTree {
	/* Overview: A data structure that represents clauses in the form of a Tree */

public:
	QUERY_NODE_POINTER createNode(NODE_TYPE node_type, QUERY_NODE_POINTERS children);
	/*
	Description:
	  Normal: Constructs a CLAUSE_NODE & returns a pointer to it.
	  Abnormal: If 'node_type' is not 'synonym' and 'children' is empty,
				or if 'node_type' is not 'such that'/'select' and does not have exactly two 'children', throw an exception.
	*/

	NODE_TYPE getNodeType();
	/*
	Requires: The node should have a valid CLAUSE_TYPE.
	Description:
	  Normal: Returns the CLAUSE_TYPE of the node.
	  Abnormal: If no such CLAUSE_TYPE exists, throws an exception.
	*/

	QUERY_NODE_POINTERS getChildren();
	/*
	Description:
	  Normal: Returns the CLAUSE_NODE_POINTERS that points to the children of the node.
	  Abnormal: If CLAUSE_NODE_POINTERS is empty, throw an exception.
	*/
};


#endif
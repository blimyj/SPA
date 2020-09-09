#include "QueryProcessor.h"
#include "QueryEvaluator.h"
#include "QueryNode.h" //REMOVE this after PreProcessor is completed

#include <unordered_map>
#include <string>

QUERY_RESULT QueryProcessor::processQuery(QUERY query) {
	/*
	* QueryPreProcessor pre_processor = QueryPreProcessor();
	* PROCESSED_QUERY process_queries = pre_processor.parse(QUERY q)
	* PROCESSED_SYNONYMS processed_synonyms = pre_processor.preProcessSynonyms(QUERY q); //returns table of synonym nodes
	* PROCESSED_CLAUSES processed_clauses = pre_processor.preProcessClauses(QUERY q); //returns query tree of clause nodes
	*/


	QueryEvaluator query_evaluator = QueryEvaluator();


	// Create fake synonyms and clauses for now
	std::unordered_map<std::string, std::string> processed_synonyms = { 
		{"assign", "a"},
		{"variable", "v"},
		{"procedure", "p"}
	};

	QueryNode processed_clauses = QueryNode(); //stores root node of the tree

	// Build fake query tree for clauses
	QueryNode child1 = QueryNode();
	child1.setNodeType("SELECT");
	QueryNode child2 = QueryNode();
	child2.setSynonymNode("SYNONYM", "a");
	QueryNode child1_children[] = { child2 };
	child1.setChildren(child1_children);


	QUERY_RESULT query_result = "";
	//QUERY_RESULT query_result = query_evaluator.evaluateQuery(processed_synonyms, processed_clauses);
	query_result = query_evaluator.evaluateQuery(processed_synonyms, processed_clauses);
	return query_result;
}


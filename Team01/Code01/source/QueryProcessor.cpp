#include "QueryProcessor.h"
#include "QueryEvaluator.h"
#include "QueryNode.h"
#include "QueryNodeType.h"
#include "QuerySynonymType.h"

#include <unordered_map>
#include <string>

QUERY_RESULT QueryProcessor::processQuery(QUERY query) {
	/*
	* QueryPreProcessor pre_processor = QueryPreProcessor();
	* PROCESSED_QUERY process_queries = pre_processor.parse(QUERY q);
	* PROCESSED_SYNONYMS processed_synonyms = pre_processor.preProcessSynonyms(QUERY q); //returns table of synonym nodes
	* PROCESSED_CLAUSES processed_clauses = pre_processor.preProcessClauses(QUERY q); //returns query tree of clause nodes
	*/


	QueryEvaluator query_evaluator = QueryEvaluator();


	// Create fake synonyms and clauses for now
	QueryNode assign_node = QueryNode();
	assign_node.setSynonymNode({ QuerySynonymType::assign }, "a");
	QueryNode variable_node = QueryNode();
	variable_node.setSynonymNode({ QuerySynonymType::variable }, "v");
	QueryNode procedure_node = QueryNode();
	procedure_node.setSynonymNode({ QuerySynonymType::procedure }, "p");
	QueryNode while_node = QueryNode();
	while_node.setSynonymNode({ QuerySynonymType::whiles }, "w");
	std::unordered_map<std::string, QueryNode> processed_synonyms = { 
		{"a", assign_node},
		{"v", variable_node},
		{"p", procedure_node},
		{"w", while_node},
	};

	QueryNode processed_clauses = QueryNode(); //stores root node of the tree

	// Build fake query tree for clauses
	// eg Select a
	QueryNode child1 = QueryNode();
	child1.setNodeType({QueryNodeType::select});
	QueryNode child2 = QueryNode();
	child2.setSynonymNode({ QuerySynonymType::assign }, "a");
	QueryNode child1_children[] = { child2 };
	child1.setChildren(child1_children);


	QUERY_RESULT query_result = "";
	//QUERY_RESULT query_result = query_evaluator.evaluateQuery(processed_synonyms, processed_clauses);
	query_result = query_evaluator.evaluateQuery(processed_synonyms, processed_clauses);
	return query_result;
}


#include "QueryProcessor.h"
#include "QueryPreProcessor.h"
#include "QueryEvaluator.h"
#include "QueryNode.h"
#include "QueryNodeType.h"
#include "QuerySynonymType.h"

#include <unordered_map>
#include <string>

QueryProcessor::QueryProcessor(){}

QueryProcessor::QueryProcessor(PKB pkb) {
	this->pkb = pkb;
}

QUERY_RESULT QueryProcessor::processQuery(QUERY query) {

	/* Uncomment when preprocessor is done
	
	// QPP
	const std::string empty_result = "";
	QueryPreProcessor pre_processor = QueryPreProcessor();
	PROCESSED_QUERY process_queries = pre_processor.parse(QUERY q);
	PROCESSED_SYNONYMS processed_synonyms = pre_processor.preProcessSynonyms(QUERY q); //returns table of synonym nodes
		if (processed_synonyms.empty()) { return empty_result; } // either no synonym or syntax error, both should return emptyresult
	PROCESSED_CLAUSES processed_clauses = pre_processor.preProcessClauses(QUERY q); //returns query tree of clause nodes
		 if (processed_queries == NULL) { return empty_result; } // null result means that there is syntax error, return empty result

	// Wait for preprocessor
	
	const std::string empty_result = "";
	QueryPreProcessor pre_processor = QueryPreProcessor();
	SPLIT_QUERY split_query = pre_processor.splitQuery(query); // returns vector containing seperated declarations and clauses
	PROCESSED_SYNONYMS processed_synonyms = pre_processor.preProcessSynonyms(split_query.at(0)); // returns table of synonym nodes
		if (processed_synonyms.empty()) { return empty_result; } // either no synonym or syntax error, both should return emptyresult
		PROCESSED_CLAUSES processed_clauses = pre_processor.preProcessClauses(processed_synonyms, split_query.at(1)); //returns query tree of clause nodes
		if (processed_clauses.getNodeType() == QueryNodeType::unassigned) { return empty_result; } // null result means that there is syntax error, return empty result
	


	// QE
	QueryEvaluator query_evaluator = QueryEvaluator(this->pkb);

	QUERY_RESULT query_result = query_evaluator.evaluateQuery(processed_synonyms, processed_clauses);
	return query_result;
	*/
	return "";

	/*
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


	// Build fake query tree for clauses
	// eg Select v such that Follows(3,v)
	QueryNode child2 = QueryNode();
	child2.setSynonymNode(QuerySynonymType::variable, "v");


	QueryNode such_that = QueryNode();
	such_that.setNodeType(QueryNodeType::such_that);

	QueryNode root = QueryNode();
	root.setNodeType(QueryNodeType::select);
	QueryNode root_children[] = { child2 };
	root.setChildren(root_children, 1);


	QueryNode processed_clauses = root; //stores root node of the tree
	*/
}


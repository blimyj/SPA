#pragma once

#include "ResultList.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iterator>

class ResultListManager;

class ResultListManager {
// Note to self: for methods that change result_list, return ResultList!
public:
	static std::string filter(std::string list1, std::string list2);
	static ResultList addSynonymAndValues(ResultList *result_list_ptr, std::string synonym_name, std::vector<std::string> synonym_values) {
		ResultList result_list = *result_list_ptr;
		result_list.addColumn(synonym_name, synonym_values);
		return result_list;
	};
	static std::string fakeMethod() {
		return "ResultListManager works";
	};
	static std::string getValues(ResultList result_list, std::string synonym_name) {
		// Return all the values of this synonym_name
		std::vector<std::string> raw_result = result_list.getValuesOfSynonym(synonym_name);
		return processReturnResult(raw_result);
	}
	static bool containsSynonym(ResultList result_list, std::string synonym_name) {
		return result_list.containsSynonym(synonym_name);
	}

private:
	static std::string processReturnResult(std::vector<std::string> raw_results) {
		std::string processed_results = "";
		for (std::string result : raw_results) {
			processed_results = processed_results + result + ", ";
		}
		return processed_results;
	};
};
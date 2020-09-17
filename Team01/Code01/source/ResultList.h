#pragma once

#include <vector>
#include <map>
#include <string>
#include <iterator>

class ResultList;

typedef std::string SYNONYM_NAME;
typedef std::vector<std::string> SYNONYM_VALUES_LIST;
typedef std::map<SYNONYM_NAME, SYNONYM_VALUES_LIST> RESULT_LIST;

class ResultList {
private:
	 RESULT_LIST results;
public:
	void addColumn(SYNONYM_NAME column_name, SYNONYM_VALUES_LIST column_values);
	void removeColumn(SYNONYM_NAME column_name);
	SYNONYM_VALUES_LIST getValuesOfSynonym(SYNONYM_NAME column_name);
	bool containsSynonym(SYNONYM_NAME column_name);
};
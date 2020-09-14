#include "ResultList.h"

void ResultList::addColumn(std::string columnName, std::vector<std::string> columnValues) {
	results.insert(std::pair<std::string, std::vector<std::string>>(columnName, columnValues));
}

void ResultList::removeColumn(std::string columnName) {
	results.erase(columnName);
}

SYNONYM_VALUES_LIST ResultList::getValuesOfSynonym(SYNONYM_NAME column_name) {
	return results[column_name];
}

bool ResultList::containsSynonym(SYNONYM_NAME column_name) {
	if (results.find(column_name) != results.end()) {
		return true;
	}
	else {
		return false;
	}
};
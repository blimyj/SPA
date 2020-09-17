#include "ResultList.h"

void ResultList::addColumn(SYNONYM_NAME columnName, SYNONYM_VALUES_LIST columnValues) {
	results.insert(std::pair<SYNONYM_NAME, SYNONYM_VALUES_LIST>(columnName, columnValues));
}

void ResultList::removeColumn(SYNONYM_NAME columnName) {
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
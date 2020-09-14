#include "ResultList.h"

void ResultList::addColumn(std::string columnName, std::vector<std::string> columnValues) {
	results.insert(std::pair(columnName, columnValues));
}
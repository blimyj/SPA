#include "ResultList.h"

void ResultList::addColumn(SYNONYM_NAME columnName) {
	results.insert({ columnName, SYNONYM_VALUES_LIST() });
}

void ResultList::addColumn(SYNONYM_NAME columnName, SYNONYM_VALUES_LIST columnValues) {
	results.insert({ columnName, columnValues });
	num_rows_ = columnValues.size();
}

void ResultList::addColumn(SYNONYM_NAME columnName, SYNONYM_INT_VALUES_LIST columnValues) {
	SYNONYM_VALUES_LIST strColumnValues;
	for (int s : columnValues) {
		strColumnValues.push_back(std::to_string(s));
	}
	ResultList::addColumn(columnName, strColumnValues);
}

void ResultList::addRow(ROW row) {
	// Iterate each column of this resultlist
	for (auto &r : results) {
		// Check if row contains that column
		auto it = row.find(r.first);
		if (it == row.end()) {
			throw "Adding a row that is missing a column required in this ResultList!";
		}
		r.second.push_back(it->second);
	}
	num_rows_++;
}

void ResultList::removeColumn(SYNONYM_NAME columnName) {
	results.erase(columnName);
}

SYNONYM_VALUES_LIST ResultList::getValuesOfSynonym(SYNONYM_NAME column_name) {
	return results[column_name];
}

bool ResultList::containsSynonym(SYNONYM_NAME column_name) {
	return results.count(column_name) > 0;
}

SYNONYM_NAME_LIST ResultList::getAllSynonyms() {
	SYNONYM_NAME_LIST all_synonyms;
	for (RESULT_LIST::iterator it = results.begin(); it != results.end(); ++it) {
		all_synonyms.push_back(it->first);
	}
	return all_synonyms;
}

ROW_LIST ResultList::getRowList() {
	ROW_LIST all_rows;
	for (int i = 0; i < num_rows_ ; ++i) {
		ROW current_row;
		for (RESULT_LIST::iterator it = results.begin(); it != results.end(); ++it) {
			SYNONYM_NAME synonym = it->first;
			SYNONYM_VALUE value = it->second.at(i);
			current_row.insert({ synonym, value });
		}
		all_rows.push_back(current_row);
	}
	return all_rows;
}

INTEGER ResultList::getNumRows() {
	return num_rows_;
}

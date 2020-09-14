#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

class ResultList;

class ResultList {
private:
	std::map<std::string, std::vector<std::string>> results;
public:
	void addColumn(std::string columnName, std::vector<std::string> columnValues);
	//removeColumn(std::string columnName);

}
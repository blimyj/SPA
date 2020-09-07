#include "GUIWrapper.h"

#include <iostream>

// a default constructor
GUIWrapper::GUIWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void GUIWrapper::parse(STRING filename) {
	// call your parser to do the parsing
<<<<<<< HEAD
	std::cout << "parsed " << filename << std::endl;
  // ...rest of your code...
=======
	std::cout << "parsed " << filename;
	parseFile(filename);
	// ...rest of your code...
>>>>>>> Change Parser assumptions
}

// method to evaluating a query
void GUIWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

	std::cout << "query=  " << query << std::endl;
	results.push_back(query + "\nQuery result: ...");
  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}

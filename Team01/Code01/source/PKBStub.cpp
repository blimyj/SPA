#include "PKBStub.h"
#include "PKB.h"
#include "PKBBuilder.h"
#include "./PKB/ASTNode/VariableNode.h"

#include <memory>

PKB PKBStub::addVariables() {
	// create some variables

	std::shared_ptr<VariableNode> svar1 = std::make_shared<VariableNode>();
	svar1->setVariableName("C++ god");
	std::shared_ptr<VariableNode> svar2 = std::make_shared<VariableNode>();
	svar2->setVariableName("Help");
	std::shared_ptr<VariableNode> svar3 = std::make_shared<VariableNode>();
	svar3->setVariableName("me");

	PKBBuilder builder;
	int i1 = builder.addVariableNode(svar1);
	int i2 = builder.addVariableNode(svar2);
	int i3 = builder.addVariableNode(svar3);
	return builder.build();

}

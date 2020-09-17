#include "PKBStub.h"
#include "PKB.h"
#include "PKBBuilder.h"
#include "./PKB/ASTNode/VariableNode.h"

#include <memory>

PKB PKBStub::addVariables() {
	// create some variables
	
	VariableNode var1 = VariableNode("C++ god");
	std::shared_ptr<VariableNode> svar1 = std::make_shared<VariableNode>(var1);
	VariableNode var2 = VariableNode("Help");
	std::shared_ptr<VariableNode> svar2 = std::make_shared<VariableNode>(var2);
	VariableNode var3 = VariableNode("me");
	std::shared_ptr<VariableNode> svar3 = std::make_shared<VariableNode>(var3);

	PKBBuilder builder;
	int i1 = builder.addVariableNode(svar1);
	int i2 = builder.addVariableNode(svar2);
	int i3 = builder.addVariableNode(svar3);
	return builder.build();
	
}

#pragma once

enum class QueryNodeType {
	select,
	synonym,
	such_that,
	parent,
	parentT,
	follows,
	followsT,
	usesS,
	modifiesS,
	pattern
};
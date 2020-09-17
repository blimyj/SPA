#pragma once

enum class QueryNodeType {
	unassigned,
	select,
	synonym,
	integer,
	ident,
	wild_card,
	expression,
	such_that,
	parent,
	parentT,
	follows,
	followsT,
	usesS,
	modifiesS,
	pattern
};
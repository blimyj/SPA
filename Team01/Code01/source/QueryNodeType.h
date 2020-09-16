#pragma once

enum class QueryNodeType {
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
	followsT
};
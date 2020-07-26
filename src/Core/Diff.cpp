#include "Diff.h"
#include "DiffVisitor.h"
#include <iostream>

std::shared_ptr<Symbol>  Diff::diff(std::shared_ptr<Symbol>  s, std::string const & argument)
{
	DiffVisitor vis(argument);
	s->Accept(&vis);
	return vis.getResult();
}

Function Diff::diff(Function const & function, std::string const & argument)
{
	DiffVisitor vis(argument);
	function.getExpression()->Accept(&vis);

	return Function(vis.getResult());
}

#include "Simplifier.h"
#include "PowerExpression.h"
#include "Constant.h"
#include "ProductExpression.h"
#include "SimplifyVisitor.h"

std::shared_ptr<Symbol>  Simplifier::Simplify(std::shared_ptr<Symbol>  s)
{
	SimplifyVisitor vis;
	s->Accept(&vis);
	return vis.getResult();
}

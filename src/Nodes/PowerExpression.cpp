#include "PowerExpression.h"

PowerSymbol::PowerSymbol(std::shared_ptr<Symbol>  expr, std::shared_ptr<Symbol> _pow)
	: Expression(expr, _pow, ExpressionType::Power)
{
}

void PowerSymbol::Accept(SymbolVisitor * v)
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	auto p{ std::dynamic_pointer_cast<type_id>(shared_from_this()) };
	v->Visit(p);
}

std::shared_ptr<Symbol>  PowerSymbol::Clone()
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	return std::make_shared<type_id>(getLeft()->Clone(), getRight()->Clone());
}


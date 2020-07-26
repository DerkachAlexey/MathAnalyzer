#include "DivideExpression.h"
#include "SymbolVisitor.h"
DivideExpression::DivideExpression(std::shared_ptr<Symbol>  _left, std::shared_ptr<Symbol>  _right)
	: Expression(_left, _right, ExpressionType::Division)
{
}

void DivideExpression::Accept(SymbolVisitor * v)
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	auto p{ std::dynamic_pointer_cast<type_id>(shared_from_this()) };
	v->Visit(p);
}

std::shared_ptr<Symbol>  DivideExpression::Clone()
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	return std::make_shared<type_id>(left->Clone(), right->Clone());
}

#include "FunctionSymbol.h"
#include "SymbolVisitor.h"

FunctionSymbol::FunctionSymbol(std::shared_ptr<Symbol> expression, FunctionType t)
	:	expr(expression), func_type(t)
{

}

std::shared_ptr<Symbol> FunctionSymbol::getExpression()
{
	return expr;
}

FunctionSymbol::FunctionType FunctionSymbol::getFunctionType() const
{
	return func_type;
}

std::shared_ptr<Symbol> FunctionSymbol::Clone()
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	return std::make_shared<type_id>(expr, func_type);
}

void FunctionSymbol::Accept(SymbolVisitor * vis)
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	auto p{ std::dynamic_pointer_cast<type_id>(shared_from_this()) };
	vis->Visit(p);
}

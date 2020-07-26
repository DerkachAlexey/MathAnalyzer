#include "ArgumentSymbol.h"
#include "SymbolVisitor.h"

ArgumentSymbol::ArgumentSymbol(std::string const & name)
	: PrimitiveSymbol(), name(name)
{
}

void ArgumentSymbol::Accept(SymbolVisitor * vis)
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	auto p{ std::dynamic_pointer_cast<type_id>(shared_from_this()) };
	vis->Visit(p);
}

std::shared_ptr<Symbol>  ArgumentSymbol::Clone()
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	return std::make_shared<type_id>(name);
}

std::string ArgumentSymbol::getValue() const
{
	return name;
}

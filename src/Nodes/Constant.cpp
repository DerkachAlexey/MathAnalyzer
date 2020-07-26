#include "Constant.h"

Constant::Constant(std::string const & _value)
	: double_value(_value)
{
}

void Constant::Accept(SymbolVisitor * v)
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	auto p{ std::dynamic_pointer_cast<type_id>(shared_from_this()) };
	v->Visit(p);
}

std::shared_ptr<Symbol>  Constant::Clone()
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	return std::make_shared<type_id>(double_value);
}

std::string Constant::getValue() const
{
	return double_value;
}

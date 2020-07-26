
#include "StringConstant.h"


void StringConstant::Accept(SymbolVisitor * v)
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	auto p{ std::dynamic_pointer_cast<type_id>(shared_from_this()) };
	v->Visit(p);
}

std::shared_ptr<Symbol>  StringConstant::Clone()
{
	using type_id = std::remove_pointer<decltype(this)>::type;
	return std::make_shared<type_id>(string_value);
}

std::string StringConstant::getValue() const
{
	return string_value;
}

StringConstant::StringConstant(std::string const & _value):
	string_value(_value)
{
}


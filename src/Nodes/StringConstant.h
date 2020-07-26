#pragma once
#include "PrimitiveSymbol.h"
#include "SymbolVisitor.h"
#include <string>

class StringConstant :
	public PrimitiveSymbol
{
	std::string string_value;
public:
	StringConstant(std::string const & _value);
	void Accept(SymbolVisitor * v) override;
	std::shared_ptr<Symbol> Clone() override;
	std::string getValue() const override;
};


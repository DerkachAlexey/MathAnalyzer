#pragma once
#include "PrimitiveSymbol.h"
#include "SymbolVisitor.h"

class Constant :
	public PrimitiveSymbol
{
	std::string double_value;
public:
	Constant(std::string const & value);
	void Accept(SymbolVisitor * v) override;
	std::shared_ptr<Symbol> Clone() override;
	std::string getValue() const override;
};


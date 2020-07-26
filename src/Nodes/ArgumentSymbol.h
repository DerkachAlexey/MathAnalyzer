#pragma once 
#include "PrimitiveSymbol.h"
#include <string>

class ArgumentSymbol
	: public PrimitiveSymbol
{
	std::string name;

public:

	ArgumentSymbol(std::string const& name);

	void Accept(SymbolVisitor * vis) override;
	std::shared_ptr<Symbol>  Clone() override;

	std::string getValue() const override;

};

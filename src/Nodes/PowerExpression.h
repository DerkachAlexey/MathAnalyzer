#pragma once
#include "Expression.h"
#include "SymbolVisitor.h"

class PowerSymbol :
	public Expression
{

public:

	PowerSymbol(std::shared_ptr<Symbol>  expr, std::shared_ptr<Symbol> pow);
	void Accept(SymbolVisitor * v) override;
	std::shared_ptr<Symbol> Clone() override;
	virtual ~PowerSymbol()
	{}

};


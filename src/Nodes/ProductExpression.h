#pragma once
#include "Expression.h"
#include "SymbolVisitor.h"
class ProductExpression :
	public Expression
{
	
public:
	ProductExpression(std::shared_ptr<Symbol>  left, std::shared_ptr<Symbol>  right);
	void Accept(SymbolVisitor * v) override;
	std::shared_ptr<Symbol> Clone() override;
	
};


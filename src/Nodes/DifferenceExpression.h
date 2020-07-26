#pragma once
#include "Expression.h"
class DifferenceExpression :
	public Expression
{

public:
	DifferenceExpression(std::shared_ptr<Symbol>  _left, std::shared_ptr<Symbol>  _right);
	void Accept(SymbolVisitor * v) override;
	std::shared_ptr<Symbol> Clone() override;
	
};


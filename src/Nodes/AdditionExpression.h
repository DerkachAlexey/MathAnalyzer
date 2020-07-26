#pragma once
#include "Expression.h"
#include "SymbolVisitor.h"
class AdditionExpression :
	public Expression
{

public:
	AdditionExpression(std::shared_ptr<Symbol>  _left, std::shared_ptr<Symbol>  _right);
	void Accept(SymbolVisitor * v) override;
	std::shared_ptr<Symbol> Clone() override;

};


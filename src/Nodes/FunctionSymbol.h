#pragma once
#include "PrimitiveSymbol.h"
#include "SymbolVisitor.h"

class FunctionSymbol :
	public Symbol
{
public:
	enum class FunctionType { 
		NaturalLogarithm,
		Cos,
		Sin
	};
private:
	std::shared_ptr<Symbol> expr;
	FunctionType func_type;
public:
	FunctionSymbol(std::shared_ptr<Symbol> expression, FunctionType type);
	std::shared_ptr<Symbol> getExpression();
	FunctionType getFunctionType() const;
	std::shared_ptr<Symbol> Clone() override;
	void Accept(SymbolVisitor * vis) override;
};


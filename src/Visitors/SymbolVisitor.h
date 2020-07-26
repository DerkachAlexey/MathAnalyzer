#pragma once
#include "Symbol.h"
class PowerSymbol;
class ProductExpression;
class AdditionExpression;
class DivideExpression;
class DifferenceExpression;
class Constant;
class ArgumentSymbol;
class FunctionSymbol;
class StringConstant;

class SymbolVisitor
{
public :
	virtual void Visit(std::shared_ptr<PowerSymbol>) = 0;
	virtual void Visit(std::shared_ptr<Constant>) = 0;
	virtual void Visit(std::shared_ptr<ProductExpression>) = 0;
	virtual void Visit(std::shared_ptr<AdditionExpression>) = 0;
	virtual void Visit(std::shared_ptr<DifferenceExpression>) = 0;
	virtual void Visit(std::shared_ptr<DivideExpression>) = 0;
	virtual void Visit(std::shared_ptr<ArgumentSymbol>) =0;
	virtual void Visit(std::shared_ptr<FunctionSymbol>) = 0;
	virtual void Visit(std::shared_ptr<StringConstant>) = 0;
	virtual ~SymbolVisitor()
	{	}
};


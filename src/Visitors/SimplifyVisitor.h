#pragma once
#include "SymbolVisitor.h"
#include "PrimitiveSymbol.h"

class Expression;
class SimplifyVisitor :
	public SymbolVisitor
{
	std::shared_ptr<Symbol>  result;

	static std::shared_ptr<Symbol>  SimplifyConstant(std::shared_ptr<Symbol>  left, std::shared_ptr<Symbol>  right, char sign);
	static std::shared_ptr<Symbol>  SimplifyExpression(std::shared_ptr<Expression> s, char sign);

	static bool IsTwoConstant(std::shared_ptr<Symbol>  left, std::shared_ptr<Symbol>  right);

public :
	std::shared_ptr<Symbol>  getResult() { return result; }
	void Visit(std::shared_ptr<PowerSymbol> ) override;
	void Visit(std::shared_ptr<Constant>) override;
	void Visit(std::shared_ptr<ProductExpression>) override;
	void Visit(std::shared_ptr<AdditionExpression>) override;
	void Visit(std::shared_ptr<DifferenceExpression>) override;
	void Visit(std::shared_ptr<DivideExpression>) override;
	void Visit(std::shared_ptr<ArgumentSymbol>) override;
	void Visit(std::shared_ptr<FunctionSymbol>) override;
	void Visit(std::shared_ptr<StringConstant>) override;
};


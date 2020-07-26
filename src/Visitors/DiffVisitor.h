#pragma once
#include "SymbolVisitor.h"
#include "Expression.h"
class DiffVisitor : public SymbolVisitor
{
	std::shared_ptr<Symbol>  result;
	std::string argument;
public :
	DiffVisitor(std::string const & argument);
	using expr_t = Expression::ExpressionType;
	std::shared_ptr<Symbol>  getResult() { return result; }
	void Visit(std::shared_ptr<PowerSymbol> ) override;
	void Visit(std::shared_ptr<Constant> ) override;
	void Visit(std::shared_ptr<ProductExpression>) override;
	void Visit(std::shared_ptr<AdditionExpression>) override;
	void Visit(std::shared_ptr<DifferenceExpression>) override;
	void Visit(std::shared_ptr<DivideExpression>) override;
	void Visit(std::shared_ptr<ArgumentSymbol>) override;
	void Visit(std::shared_ptr<FunctionSymbol>) override;
	void Visit(std::shared_ptr<StringConstant>) override;
private:
	void diffNaturalLog(std::shared_ptr<FunctionSymbol>);
	void diffCos(std::shared_ptr<FunctionSymbol>);
	void diffSin(std::shared_ptr<FunctionSymbol>);
}; 


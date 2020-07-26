#pragma once 
#include "SymbolVisitor.h"
#include "ComputeUtils.h"

class ComputeVisitor 
	: public SymbolVisitor
{
	ComputeResult result;
	ComputeContext & context;

public:

	ComputeVisitor(ComputeContext & context);

	ComputeResult getResult() { return result; }
	void Visit(std::shared_ptr<PowerSymbol>) override;
	void Visit(std::shared_ptr<Constant>) override;
	void Visit(std::shared_ptr<ProductExpression>) override;
	void Visit(std::shared_ptr<AdditionExpression>) override;
	void Visit(std::shared_ptr<DifferenceExpression>) override;
	void Visit(std::shared_ptr<DivideExpression>) override;
	void Visit(std::shared_ptr<ArgumentSymbol>) override;
	void Visit(std::shared_ptr<FunctionSymbol>) override;
	void Visit(std::shared_ptr<StringConstant>) override;
};
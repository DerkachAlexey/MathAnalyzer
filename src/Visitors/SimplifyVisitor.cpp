#include "SimplifyVisitor.h"
#include "PowerExpression.h"
#include "Constant.h"
#include "AdditionExpression.h"
#include "ProductExpression.h"
#include "DifferenceExpression.h"
#include "DivideExpression.h"
#include "ArgumentSymbol.h"
#include "StringConstant.h"
#include "Computer.h"
#include "SymbolFactory.h"


std::shared_ptr<Symbol>  SimplifyVisitor::SimplifyConstant(std::shared_ptr<Symbol>  left, std::shared_ptr<Symbol>  right, char sign)
{
	std::shared_ptr<Constant> l, r;
	l = std::dynamic_pointer_cast<Constant>(left);
	r = std::dynamic_pointer_cast<Constant>(right);

	switch (sign)
	{
	case '+':
		return SymbolFactory::createSymbol( (std::stod(l->getValue()) + std::stod(r->getValue())));
	case '-':
		return SymbolFactory::createSymbol((std::stod(l->getValue()) - std::stod(r->getValue())));
	case '*':
		return SymbolFactory::createSymbol((std::stod(l->getValue()) * std::stod(r->getValue())));
	case '/':
		return SymbolFactory::createSymbol((std::stod(l->getValue()) / std::stod(r->getValue())));
	case '^':
		return SymbolFactory::createSymbol((std::stod(l->getValue()) + std::stod(r->getValue())));
	default:
		throw std::runtime_error("unknown sign in SimplifyConstant");
	}

}

std::shared_ptr<Symbol> SimplifyVisitor::SimplifyExpression(std::shared_ptr<Expression> s, char sign)
{
	std::shared_ptr<Symbol> result;

	SimplifyVisitor rightVis;
	s->getRight()->Accept(&rightVis);
	SimplifyVisitor leftVis;
	s->getLeft()->Accept(&leftVis);

	if (IsTwoConstant(leftVis.getResult(), rightVis.getResult()))
	{
		return SimplifyConstant(leftVis.getResult(), rightVis.getResult(), sign);
	}

	if (rightVis.getResult() && leftVis.getResult())
		return SymbolFactory::createExpression(leftVis.getResult(), rightVis.getResult(), sign);
}



bool SimplifyVisitor::IsTwoConstant(std::shared_ptr<Symbol>  left, std::shared_ptr<Symbol>  right)
{
	std::shared_ptr<Constant> l, r;
	l = std::dynamic_pointer_cast<Constant>(left);
	r = std::dynamic_pointer_cast<Constant>(right);
	return l && r;
}

void SimplifyVisitor::Visit(std::shared_ptr<PowerSymbol> s)
{
	result = SimplifyExpression(s, '^');
}

void SimplifyVisitor::Visit(std::shared_ptr < Constant > s)
{
	result = s->Clone();
}

void SimplifyVisitor::Visit(std::shared_ptr<ProductExpression>s)
{
	result = SimplifyExpression(s, '*');
}

void SimplifyVisitor::Visit(std::shared_ptr < AdditionExpression> s)
{
	result = SimplifyExpression(s, '+');
}

void SimplifyVisitor::Visit(std::shared_ptr < DifferenceExpression>  s)
{
	result = SimplifyExpression(s, '-');
}

void SimplifyVisitor::Visit(std::shared_ptr < DivideExpression> s)
{
	result = SimplifyExpression(s, '/');

}

void SimplifyVisitor::Visit(std::shared_ptr<ArgumentSymbol>  s)
{
	//FIXME
	result = s->Clone();
}

void SimplifyVisitor::Visit(std::shared_ptr<FunctionSymbol> s)
{
	//FIXME
	result = s->Clone();
}

void SimplifyVisitor::Visit(std::shared_ptr<StringConstant> s)
{
	//FIXME
	result = s->Clone();
}
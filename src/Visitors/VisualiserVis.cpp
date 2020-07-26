#include "VisualiserVis.h"
#include "PowerExpression.h"
#include "Constant.h"
#include "AdditionExpression.h"
#include "ProductExpression.h"
#include "DivideExpression.h"
#include "DifferenceExpression.h"
#include "FunctionSymbol.h"
#include "ArgumentSymbol.h"
#include "StringConstant.h"

void VisualiserVis::Visit(std::shared_ptr<PowerSymbol> s)
{
	VisualiserVis exprVis;
	VisualiserVis powVis;

	s->getLeft()->Accept(&exprVis);
	s->getRight()->Accept(&powVis);

	result = (exprVis.getResult() + " ^ " + powVis.getResult() + ' ');

}

void VisualiserVis::Visit(std::shared_ptr < Constant> s)
{
	result = s->getValue() + ' ';
}

void VisualiserVis::Visit(std::shared_ptr < ProductExpression> s)
{
	VisualiserVis leftVis;
	s->getLeft()->Accept(&leftVis);
	VisualiserVis rightVis;
	s->getRight()->Accept(&rightVis);

	result = "( " + leftVis.getResult() + " * " + rightVis.getResult() + ") ";
}

void VisualiserVis::Visit(std::shared_ptr < AdditionExpression> s)
{
	VisualiserVis leftVis;
	s->getLeft()->Accept(&leftVis);
	VisualiserVis rightVis;
	s->getRight()->Accept(&rightVis);

	result = "( " + leftVis.getResult() + " + " + rightVis.getResult() + ") ";
}

void VisualiserVis::Visit(std::shared_ptr < DifferenceExpression> s)
{
	VisualiserVis leftVis;
	s->getLeft()->Accept(&leftVis);
	VisualiserVis rightVis;
	s->getRight()->Accept(&rightVis);

	result = "( " + leftVis.getResult() + " - " + rightVis.getResult() + ") ";
}

void VisualiserVis::Visit(std::shared_ptr < DivideExpression> s)
{
	VisualiserVis leftVis;
	s->getLeft()->Accept(&leftVis);
	VisualiserVis rightVis;
	s->getRight()->Accept(&rightVis);

	result = "( " + leftVis.getResult() + " / " + rightVis.getResult() + ") ";
}

void VisualiserVis::Visit(std::shared_ptr<ArgumentSymbol> s)
{
	result = (s->getValue());
}

void VisualiserVis::Visit(std::shared_ptr<FunctionSymbol> s)
{
	VisualiserVis vis_expression;
	s->getExpression()->Accept(&vis_expression);	switch (s->getFunctionType())
	{
	case FunctionSymbol::FunctionType::NaturalLogarithm:
		result = "ln(" + vis_expression.getResult() + ")";
		break;
	case FunctionSymbol::FunctionType::Cos:
		result = "cos(" + vis_expression.getResult() + ")";
		break;
	case FunctionSymbol::FunctionType::Sin:
		result = "sin(" + vis_expression.getResult() + ")";
		break;
	default:
		break;
	}
}

void VisualiserVis::Visit(std::shared_ptr<StringConstant> s)
{
	result = (s->getValue());}
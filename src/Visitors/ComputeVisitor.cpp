#include "ComputeVisitor.h"
#include "PowerExpression.h"
#include "Constant.h"
#include "AdditionExpression.h"
#include "ProductExpression.h"
#include "DifferenceExpression.h"
#include "DivideExpression.h"
#include "ArgumentSymbol.h"
#include "FunctionSymbol.h"
#include "StringConstant.h"
#include <algorithm>

ComputeVisitor::ComputeVisitor(ComputeContext & context)
	: context(context)
{
}

void ComputeVisitor::Visit(std::shared_ptr<PowerSymbol> s)
{
	ComputeVisitor exprVis(context);
	ComputeVisitor powVis(context);

	s->getLeft()->Accept(&exprVis);
	s->getRight()->Accept(&powVis);

	ComputeResult rightRes = powVis.getResult();
	ComputeResult leftRes = exprVis.getResult();


	result.SetValue(std::pow(leftRes.GetValue(), rightRes.GetValue()));

	result.MergeRequiredArgs(leftRes.GetRequiredArgs());
	result.MergeRequiredArgs(rightRes.GetRequiredArgs());

	result.MergeStringConstants(leftRes.GetStringConsts());
	result.MergeStringConstants(rightRes.GetStringConsts());

}

void ComputeVisitor::Visit(std::shared_ptr<Constant> s)
{
	result.SetValue(std::stod(s->getValue()));
}

void ComputeVisitor::Visit(std::shared_ptr < ProductExpression> s)
{
	ComputeVisitor rightVis(context);
	s->getRight()->Accept(&rightVis);
	ComputeVisitor leftVis(context);
	s->getLeft()->Accept(&leftVis);
	ComputeResult rightRes = rightVis.getResult();
	ComputeResult leftRes = leftVis.getResult();


	result.SetValue(leftRes.GetValue() * rightRes.GetValue());


	result.MergeRequiredArgs(leftRes.GetRequiredArgs());
	result.MergeRequiredArgs(rightRes.GetRequiredArgs());

	result.MergeStringConstants(leftRes.GetStringConsts());
	result.MergeStringConstants(rightRes.GetStringConsts());
}

void ComputeVisitor::Visit(std::shared_ptr < AdditionExpression> s)
{
	ComputeVisitor rightVis(context);
	s->getRight()->Accept(&rightVis);
	ComputeVisitor leftVis(context);
	s->getLeft()->Accept(&leftVis);
	
	ComputeResult rightRes = rightVis.getResult();
	ComputeResult leftRes = leftVis.getResult();


	result.SetValue(leftRes.GetValue() + rightRes.GetValue());


	result.MergeRequiredArgs(leftRes.GetRequiredArgs());
	result.MergeRequiredArgs(rightRes.GetRequiredArgs());

	result.MergeStringConstants(leftRes.GetStringConsts());
	result.MergeStringConstants(rightRes.GetStringConsts());
}

void ComputeVisitor::Visit(std::shared_ptr < DifferenceExpression> s)
{
	ComputeVisitor rightVis(context);
	s->getRight()->Accept(&rightVis);
	ComputeVisitor leftVis(context);
	s->getLeft()->Accept(&leftVis);

	ComputeResult rightRes = rightVis.getResult();
	ComputeResult leftRes = leftVis.getResult();


	result.SetValue(leftRes.GetValue() - rightRes.GetValue());


	result.MergeRequiredArgs(leftRes.GetRequiredArgs());
	result.MergeRequiredArgs(rightRes.GetRequiredArgs());

	result.MergeStringConstants(leftRes.GetStringConsts());
	result.MergeStringConstants(rightRes.GetStringConsts());
}

void ComputeVisitor::Visit(std::shared_ptr < DivideExpression> s)
{
	ComputeVisitor rightVis(context);
	s->getRight()->Accept(&rightVis);
	ComputeVisitor leftVis(context);
	s->getLeft()->Accept(&leftVis);

	ComputeResult rightRes = rightVis.getResult();
	ComputeResult leftRes = leftVis.getResult();

	result.SetValue(leftRes.GetValue() / rightRes.GetValue());

	result.MergeRequiredArgs(leftRes.GetRequiredArgs());
	result.MergeRequiredArgs(rightRes.GetRequiredArgs());

	result.MergeStringConstants(leftRes.GetStringConsts());
	result.MergeStringConstants(rightRes.GetStringConsts());

}

void ComputeVisitor::Visit(std::shared_ptr<ArgumentSymbol> s)
{
	if (context.HasVariable(s->getValue()))
		result.SetValue(context.GetVariable(s->getValue()));
	else
	{

		throw std::runtime_error("invalid amount of arguments was passed");
		//result.AddRequiredArg(s->getName());
		//result.SetValue(0);
	}
}

void ComputeVisitor::Visit(std::shared_ptr<FunctionSymbol> s)
{
	ComputeVisitor exprVis(context);
	s->getExpression()->Accept(&exprVis);

	ComputeResult exprRes = exprVis.getResult();

	if (exprRes.IsValue())
	{
		switch (s->getFunctionType())
		{
		case FunctionSymbol::FunctionType::Cos:
			result.SetValue(std::cos(exprRes.GetValue()));
			break;
		case FunctionSymbol::FunctionType::NaturalLogarithm:
			result.SetValue(std::log(exprRes.GetValue()));
			break;
		case FunctionSymbol::FunctionType::Sin:
			result.SetValue(std::sin(exprRes.GetValue()));
			break;
		default:
			break;
		}
	}

	result.MergeRequiredArgs(exprRes.GetRequiredArgs());
}

void ComputeVisitor::Visit(std::shared_ptr<StringConstant> s)
{
	result.AddStringConstans(s->getValue());
	result.SetValue(0);
}